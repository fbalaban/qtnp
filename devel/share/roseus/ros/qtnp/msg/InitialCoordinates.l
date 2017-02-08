;; Auto-generated. Do not edit!


(when (boundp 'qtnp::InitialCoordinates)
  (if (not (find-package "QTNP"))
    (make-package "QTNP"))
  (shadow 'InitialCoordinates (find-package "QTNP")))
(unless (find-package "QTNP::INITIALCOORDINATES")
  (make-package "QTNP::INITIALCOORDINATES"))

(in-package "ROS")
;;//! \htmlinclude InitialCoordinates.msg.html


(defclass qtnp::InitialCoordinates
  :super ros::object
  :slots (_uav_id _longitude _latitude ))

(defmethod qtnp::InitialCoordinates
  (:init
   (&key
    ((:uav_id __uav_id) 0)
    ((:longitude __longitude) 0.0)
    ((:latitude __latitude) 0.0)
    )
   (send-super :init)
   (setq _uav_id (round __uav_id))
   (setq _longitude (float __longitude))
   (setq _latitude (float __latitude))
   self)
  (:uav_id
   (&optional __uav_id)
   (if __uav_id (setq _uav_id __uav_id)) _uav_id)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:serialization-length
   ()
   (+
    ;; int8 _uav_id
    1
    ;; float64 _longitude
    8
    ;; float64 _latitude
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _uav_id
       (write-byte _uav_id s)
     ;; float64 _longitude
       (sys::poke _longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _latitude
       (sys::poke _latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _uav_id
     (setq _uav_id (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _uav_id 127) (setq _uav_id (- _uav_id 256)))
   ;; float64 _longitude
     (setq _longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _latitude
     (setq _latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get qtnp::InitialCoordinates :md5sum-) "d5d8ffa4c93324dbf2bbc015565b6f30")
(setf (get qtnp::InitialCoordinates :datatype-) "qtnp/InitialCoordinates")
(setf (get qtnp::InitialCoordinates :definition-)
      "int8 uav_id
float64 longitude
float64 latitude

")



(provide :qtnp/InitialCoordinates "d5d8ffa4c93324dbf2bbc015565b6f30")


