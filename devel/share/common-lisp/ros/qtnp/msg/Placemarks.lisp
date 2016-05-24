; Auto-generated. Do not edit!


(cl:in-package qtnp-msg)


;//! \htmlinclude Placemarks.msg.html

(cl:defclass <Placemarks> (roslisp-msg-protocol:ros-message)
  ((placemark
    :reader placemark
    :initarg :placemark
    :type (cl:vector qtnp-msg:Coordinates)
   :initform (cl:make-array 0 :element-type 'qtnp-msg:Coordinates :initial-element (cl:make-instance 'qtnp-msg:Coordinates))))
)

(cl:defclass Placemarks (<Placemarks>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Placemarks>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Placemarks)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name qtnp-msg:<Placemarks> is deprecated: use qtnp-msg:Placemarks instead.")))

(cl:ensure-generic-function 'placemark-val :lambda-list '(m))
(cl:defmethod placemark-val ((m <Placemarks>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader qtnp-msg:placemark-val is deprecated.  Use qtnp-msg:placemark instead.")
  (placemark m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Placemarks>) ostream)
  "Serializes a message object of type '<Placemarks>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'placemark))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'placemark))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Placemarks>) istream)
  "Deserializes a message object of type '<Placemarks>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'placemark) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'placemark)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'qtnp-msg:Coordinates))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Placemarks>)))
  "Returns string type for a message object of type '<Placemarks>"
  "qtnp/Placemarks")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Placemarks)))
  "Returns string type for a message object of type 'Placemarks"
  "qtnp/Placemarks")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Placemarks>)))
  "Returns md5sum for a message object of type '<Placemarks>"
  "b4349b45ce3a0b7fe1423d1ecf4c71cb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Placemarks)))
  "Returns md5sum for a message object of type 'Placemarks"
  "b4349b45ce3a0b7fe1423d1ecf4c71cb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Placemarks>)))
  "Returns full string definition for message of type '<Placemarks>"
  (cl:format cl:nil "qtnp/Coordinates[] placemark ~%~%================================================================================~%MSG: qtnp/Coordinates~%string placemark_type~%float64[] longitude~%float64[] latitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Placemarks)))
  "Returns full string definition for message of type 'Placemarks"
  (cl:format cl:nil "qtnp/Coordinates[] placemark ~%~%================================================================================~%MSG: qtnp/Coordinates~%string placemark_type~%float64[] longitude~%float64[] latitude~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Placemarks>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'placemark) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Placemarks>))
  "Converts a ROS message object to a list"
  (cl:list 'Placemarks
    (cl:cons ':placemark (placemark msg))
))
