; Auto-generated. Do not edit!


(cl:in-package OryxMessages-msg)


;//! \htmlinclude WheelVelocities.msg.html

(cl:defclass <WheelVelocities> (roslisp-msg-protocol:ros-message)
  ((left_front_wheel
    :reader left_front_wheel
    :initarg :left_front_wheel
    :type cl:float
    :initform 0.0)
   (right_front_wheel
    :reader right_front_wheel
    :initarg :right_front_wheel
    :type cl:float
    :initform 0.0)
   (left_rear_wheel
    :reader left_rear_wheel
    :initarg :left_rear_wheel
    :type cl:float
    :initform 0.0)
   (right_rear_wheel
    :reader right_rear_wheel
    :initarg :right_rear_wheel
    :type cl:float
    :initform 0.0))
)

(cl:defclass WheelVelocities (<WheelVelocities>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <WheelVelocities>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'WheelVelocities)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name OryxMessages-msg:<WheelVelocities> is deprecated: use OryxMessages-msg:WheelVelocities instead.")))

(cl:ensure-generic-function 'left_front_wheel-val :lambda-list '(m))
(cl:defmethod left_front_wheel-val ((m <WheelVelocities>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader OryxMessages-msg:left_front_wheel-val is deprecated.  Use OryxMessages-msg:left_front_wheel instead.")
  (left_front_wheel m))

(cl:ensure-generic-function 'right_front_wheel-val :lambda-list '(m))
(cl:defmethod right_front_wheel-val ((m <WheelVelocities>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader OryxMessages-msg:right_front_wheel-val is deprecated.  Use OryxMessages-msg:right_front_wheel instead.")
  (right_front_wheel m))

(cl:ensure-generic-function 'left_rear_wheel-val :lambda-list '(m))
(cl:defmethod left_rear_wheel-val ((m <WheelVelocities>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader OryxMessages-msg:left_rear_wheel-val is deprecated.  Use OryxMessages-msg:left_rear_wheel instead.")
  (left_rear_wheel m))

(cl:ensure-generic-function 'right_rear_wheel-val :lambda-list '(m))
(cl:defmethod right_rear_wheel-val ((m <WheelVelocities>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader OryxMessages-msg:right_rear_wheel-val is deprecated.  Use OryxMessages-msg:right_rear_wheel instead.")
  (right_rear_wheel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <WheelVelocities>) ostream)
  "Serializes a message object of type '<WheelVelocities>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'left_front_wheel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'right_front_wheel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'left_rear_wheel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'right_rear_wheel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <WheelVelocities>) istream)
  "Deserializes a message object of type '<WheelVelocities>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'left_front_wheel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'right_front_wheel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'left_rear_wheel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'right_rear_wheel) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<WheelVelocities>)))
  "Returns string type for a message object of type '<WheelVelocities>"
  "OryxMessages/WheelVelocities")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'WheelVelocities)))
  "Returns string type for a message object of type 'WheelVelocities"
  "OryxMessages/WheelVelocities")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<WheelVelocities>)))
  "Returns md5sum for a message object of type '<WheelVelocities>"
  "ce91d1774d95f0a86e888d5fe76a8af6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'WheelVelocities)))
  "Returns md5sum for a message object of type 'WheelVelocities"
  "ce91d1774d95f0a86e888d5fe76a8af6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<WheelVelocities>)))
  "Returns full string definition for message of type '<WheelVelocities>"
  (cl:format cl:nil "#Swerve positions, in radians~%float64 left_front_wheel~%float64 right_front_wheel~%float64 left_rear_wheel~%float64 right_rear_wheel~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'WheelVelocities)))
  "Returns full string definition for message of type 'WheelVelocities"
  (cl:format cl:nil "#Swerve positions, in radians~%float64 left_front_wheel~%float64 right_front_wheel~%float64 left_rear_wheel~%float64 right_rear_wheel~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <WheelVelocities>))
  (cl:+ 0
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <WheelVelocities>))
  "Converts a ROS message object to a list"
  (cl:list 'WheelVelocities
    (cl:cons ':left_front_wheel (left_front_wheel msg))
    (cl:cons ':right_front_wheel (right_front_wheel msg))
    (cl:cons ':left_rear_wheel (left_rear_wheel msg))
    (cl:cons ':right_rear_wheel (right_rear_wheel msg))
))
