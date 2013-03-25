#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include <sstream>

#include "RoboteqDevice.h"
#include "ErrorCodes.h"

using namespace std;

#define BUFFER_SIZE 1024
#define MISSING_VALUE -1024

RoboteqDevice::RoboteqDevice()
{
}
RoboteqDevice::~RoboteqDevice()
{
	Disconnect();
}

bool RoboteqDevice::IsConnected()
{
  return serial_port.is_open();
}
int RoboteqDevice::Connect(string port)
{
	if(IsConnected())
	{
		cout<<"Device is connected, attempting to disconnect."<<endl;
		Disconnect();
	}

	if(serial_port.open(port, B9600, 7, serial_parity_even)<0){
	  cout<<"Opening port: '"<<port<<"'..."<<"failed."<<endl;
	  return RQ_ERR_OPEN_PORT;
	}
	cout<<"Opening port: '"<<port<<"'..."<<"succeeded."<<endl;

	int status;
	string response;
	cout<<"Detecting device version...";
	status = IssueCommand("?", "$1E", 10, response);
	if(status != RQ_SUCCESS)
	{
		cout<<"failed (issue ?$1E response: "<<status<<")."<<endl;
		Disconnect();
		return RQ_UNRECOGNIZED_DEVICE;
	}

	if(response.length() < 12)
	{
		cout<<"failed (unrecognized version)."<<endl;
		Disconnect();
		return RQ_UNRECOGNIZED_VERSION;
	}

	cout<<response<<"."<<endl;
	return RQ_SUCCESS;
}
void RoboteqDevice::Disconnect()
{
	if(IsConnected())
		serial_port.close();
}

int RoboteqDevice::Write(string str)
{
	if(!IsConnected())
		return RQ_ERR_NOT_CONNECTED;

	//cout<<"Writing: "<<ReplaceString(str, "\r", "\r\n");
	int countSent = serial_port.write(str.c_str(), str.length(), 10);

	//Verify weather the Transmitting Data on UART was Successful or Not
	if(countSent < 0)
		return RQ_ERR_TRANSMIT_FAILED;

	return RQ_SUCCESS;
}

int RoboteqDevice::IssueCommand(string commandType, string command, string args, int waitms, string &response, bool isplusminus)
{
	int status;
	string read;
	response = "";

	if(args == "")
		status = Write(commandType + command + "\r");
	else
		status = Write(commandType + command + " " + args + "\r");

	if(status != RQ_SUCCESS)
		return status;

	char buf[BUFFER_SIZE];
	while((status = serial_port.read_line(buf, BUFFER_SIZE, '\r', 10))>=0){//read in command echo
	  //cout << "Got command echo: "<<buf<<endl;
	  if(strstr(buf, (commandType+command).c_str())==buf)
	    break;
	}
	if(status<=0){
	  //cout << "Got echo read status: "<<status<<" errno="<<errno<<" buf="<<buf<<endl;
	  return status;
	}

	status = serial_port.read_line(buf, BUFFER_SIZE, '\r', 10);//read in result
	//cout << "Got command value: "<<buf<<endl;
	if(status<0)
		return status;

	response = buf;

	if(isplusminus)
	{
	  if(status != 1)//length of response
	    return RQ_INVALID_RESPONSE;
	  return RQ_SUCCESS;
	}


	string::size_type pos = response.rfind(command + "=");
	if(pos == string::npos)
		return RQ_INVALID_RESPONSE;

	pos += command.length() + 1;

	response = response.substr(pos, status - pos);

	return RQ_SUCCESS;
}
int RoboteqDevice::IssueCommand(string commandType, string command, int waitms, string &response, bool isplusminus)
{
	return IssueCommand(commandType, command, "", waitms, response, isplusminus);
}

int RoboteqDevice::SetConfig(int configItem, int index, int value)
{
	string response;
	char command[10];
	char args[50];

	if(configItem < 0 || configItem > 255)
		return RQ_INVALID_CONFIG_ITEM;

	sprintf(command, "$%02X", configItem);
	sprintf(args, "%i %i", index, value);
	if(index == MISSING_VALUE)
	{
		sprintf(args, "%i", value);
		index = 0;
	}

	if(index < 0)
		return RQ_INDEX_OUT_RANGE;

	int status = IssueCommand("^", command, args, 10, response, true);
	if(status != RQ_SUCCESS)
		return status;
	if(response != "+")
		return RQ_SET_CONFIG_FAILED;

	return RQ_SUCCESS;
}
int RoboteqDevice::SetConfig(int configItem, int value)
{
	return SetConfig(configItem, MISSING_VALUE, value);
}

int RoboteqDevice::SetCommand(int commandItem, int index, int value)
{
	string response;
	char command[10];
	char args[50];

	if(commandItem < 0 || commandItem > 255)
		return RQ_INVALID_COMMAND_ITEM;

	sprintf(command, "$%02X", commandItem);
	sprintf(args, "%i %i", index, value);
	if(index == MISSING_VALUE)
	{
		if(value != MISSING_VALUE)
			sprintf(args, "%i", value);
		index = 0;
	}

	if(index < 0)
		return RQ_INDEX_OUT_RANGE;

	int status = IssueCommand("!", command, args, 10, response, true);
	if(status != RQ_SUCCESS)
		return status;
	if(response != "+")
		return RQ_SET_COMMAND_FAILED;

	return RQ_SUCCESS;
}
int RoboteqDevice::SetCommand(int commandItem, int value)
{
	return SetCommand(commandItem, MISSING_VALUE, value);
}
int RoboteqDevice::SetCommand(int commandItem)
{
	return SetCommand(commandItem, MISSING_VALUE, MISSING_VALUE);
}

int RoboteqDevice::GetConfig(int configItem, int index, int &result)
{
	string response;
	char command[10];
	char args[50];

	if(configItem < 0 || configItem > 255)
		return RQ_INVALID_CONFIG_ITEM;

	if(index < 0)
		return RQ_INDEX_OUT_RANGE;

	sprintf(command, "$%02X", configItem);
	sprintf(args, "%i", index);

	int status = IssueCommand("~", command, args, 10, response);
	if(status != RQ_SUCCESS)
		return status;

	istringstream iss(response);
	iss>>result;

	if(iss.fail())
		return RQ_GET_CONFIG_FAILED;

	return RQ_SUCCESS;
}
int RoboteqDevice::GetConfig(int configItem, int &result)
{
	return GetConfig(configItem, 0, result);
}

int RoboteqDevice::GetValue(int operatingItem, int index, int &result)
{
	string response;
	char command[10];
	char args[50];

	if(operatingItem < 0 || operatingItem > 255)
		return RQ_INVALID_OPER_ITEM;

	if(index < 0)
		return RQ_INDEX_OUT_RANGE;

	sprintf(command, "$%02X", operatingItem);
	sprintf(args, "%i", index);

	int status = IssueCommand("?", command, args, 10, response);
	if(status != RQ_SUCCESS)
		return status;

	istringstream iss(response);
	iss>>result;

	if(iss.fail())
		return RQ_GET_VALUE_FAILED;

	return RQ_SUCCESS;
}
int RoboteqDevice::GetValue(int operatingItem, int &result)
{
	return GetValue(operatingItem, 0, result);
}


