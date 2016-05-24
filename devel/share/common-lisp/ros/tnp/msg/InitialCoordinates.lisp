; Auto-generated. Do not edit!


(cl:in-package tnp-msg)


;//! \htmlinclude InitialCoordinates.msg.html

(cl:defclass <InitialCoordinates> (roslisp-msg-protocol:ros-message)
  ((uav_id
    :reader uav_id
    :initarg :uav_id
    :type cl:fixnum
    :initform 0)
   (longitude
    :reader longitude
    :initarg :longitude
    :type cl:float
    :initform 0.0)
   (latitude
    :reader latitude
    :initarg :latitude
    :type cl:float
    :initform 0.0))
)

(cl:defclass InitialCoordinates (<InitialCoordinates>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <InitialCoordinates>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'InitialCoordinates)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name tnp-msg:<InitialCoordinates> is deprecated: use tnp-msg:InitialCoordinates instead.")))

(cl:ensure-generic-function 'uav_id-val :lambda-list '(m))
(cl:defmethod uav_id-val ((m <InitialCoordinates>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tnp-msg:uav_id-val is deprecated.  Use tnp-msg:uav_id instead.")
  (uav_id m))

(cl:ensure-generic-function 'longitude-val :lambda-list '(m))
(cl:defmethod longitude-val ((m <InitialCoordinates>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tnp-msg:longitude-val is deprecated.  Use tnp-msg:longitude instead.")
  (longitude m))

(cl:ensure-generic-function 'latitude-val :lambda-list '(m))
(cl:defmethod latitude-val ((m <InitialCoordinates>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tnp-msg:latitude-val is deprecated.  Use tnp-msg:latitude instead.")
  (latitude m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <InitialCoordinates>) ostream)
  "Serializes a message object of type '<InitialCoordinates>"
  (cl:let* ((signed (cl:slot-value msg 'uav_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'longitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'latitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <InitialCoordinates>) istream)
  "Deserializes a message object of type '<InitialCoordinates>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'uav_id) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'longitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'latitude) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<InitialCoordinates>)))
  "Returns string type for a message object of type '<InitialCoordinates>"
  "tnp/InitialCoordinates")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'InitialCoordinates)))
  "Returns string type for a message object of type 'InitialCoordinates"
  "tnp/InitialCoordinates")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<InitialCoordinates>)))
  "Returns md5sum for a message object of type '<InitialCoordinates>"
  "d5d8ffa4c93324dbf2bbc015565b6f30")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'InitialCoordinates)))
  "Returns md5sum for a message object of type 'InitialCoordinates"
  "d5d8ffa4c93324dbf2bbc015565b6f30")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<InitialCoordinates>)))
  "Returns full string definition for message of type '<InitialCoordinates>"
  (cl:format cl:nil "int8 uav_id~%float64 longitude~%float64 latitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'InitialCoordinates)))
  "Returns full string definition for message of type 'InitialCoordinates"
  (cl:format cl:nil "int8 uav_id~%float64 longitude~%float64 latitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <InitialCoordinates>))
  (cl:+ 0
     1
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <InitialCoordinates>))
  "Converts a ROS message object to a list"
  (cl:list 'InitialCoordinates
    (cl:cons ':uav_id (uav_id msg))
    (cl:cons ':longitude (longitude msg))
    (cl:cons ':latitude (latitude msg))
))
