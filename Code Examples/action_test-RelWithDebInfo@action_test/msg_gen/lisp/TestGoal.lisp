; Auto-generated. Do not edit!


(cl:in-package action_test-msg)


;//! \htmlinclude TestGoal.msg.html

(cl:defclass <TestGoal> (roslisp-msg-protocol:ros-message)
  ((request
    :reader request
    :initarg :request
    :type cl:integer
    :initform 0))
)

(cl:defclass TestGoal (<TestGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TestGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TestGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name action_test-msg:<TestGoal> is deprecated: use action_test-msg:TestGoal instead.")))

(cl:ensure-generic-function 'request-val :lambda-list '(m))
(cl:defmethod request-val ((m <TestGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader action_test-msg:request-val is deprecated.  Use action_test-msg:request instead.")
  (request m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TestGoal>) ostream)
  "Serializes a message object of type '<TestGoal>"
  (cl:let* ((signed (cl:slot-value msg 'request)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TestGoal>) istream)
  "Deserializes a message object of type '<TestGoal>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'request) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TestGoal>)))
  "Returns string type for a message object of type '<TestGoal>"
  "action_test/TestGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TestGoal)))
  "Returns string type for a message object of type 'TestGoal"
  "action_test/TestGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TestGoal>)))
  "Returns md5sum for a message object of type '<TestGoal>"
  "650f0ccd41c8f8d53ada80be6ddde434")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TestGoal)))
  "Returns md5sum for a message object of type 'TestGoal"
  "650f0ccd41c8f8d53ada80be6ddde434")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TestGoal>)))
  "Returns full string definition for message of type '<TestGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%int32 request~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TestGoal)))
  "Returns full string definition for message of type 'TestGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%#goal definition~%int32 request~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TestGoal>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TestGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'TestGoal
    (cl:cons ':request (request msg))
))
