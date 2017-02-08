;; Auto-generated. Do not edit!


(when (boundp 'qtnp::Coordinates)
  (if (not (find-package "QTNP"))
    (make-package "QTNP"))
  (shadow 'Coordinates (find-package "QTNP")))
(unless (find-package "QTNP::COORDINATES")
  (make-package "QTNP::COORDINATES"))

(in-package "ROS")
;;//! \htmlinclude Coordinates.msg.html


(defclass qtnp::Coordinates
  :super ros::object
  :slots (_placemark_type _seed_longitude _seed_latitude _longitude _latitude ))

(defmethod qtnp::Coordinates
  (:init
   (&key
    ((:placemark_type __placemark_type) "")
    ((:seed_longitude __seed_longitude) 0.0)
    ((:seed_latitude __seed_latitude) 0.0)
    ((:longitude __longitude) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:latitude __latitude) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _placemark_type (string __placemark_type))
   (setq _seed_longitude (float __seed_longitude))
   (setq _seed_latitude (float __seed_latitude))
   (setq _longitude __longitude)
   (setq _latitude __latitude)
   self)
  (:placemark_type
   (&optional __placemark_type)
   (if __placemark_type (setq _placemark_type __placemark_type)) _placemark_type)
  (:seed_longitude
   (&optional __seed_longitude)
   (if __seed_longitude (setq _seed_longitude __seed_longitude)) _seed_longitude)
  (:seed_latitude
   (&optional __seed_latitude)
   (if __seed_latitude (setq _seed_latitude __seed_latitude)) _seed_latitude)
  (:longitude
   (&optional __longitude)
   (if __longitude (setq _longitude __longitude)) _longitude)
  (:latitude
   (&optional __latitude)
   (if __latitude (setq _latitude __latitude)) _latitude)
  (:serialization-length
   ()
   (+
    ;; string _placemark_type
    4 (length _placemark_type)
    ;; float64 _seed_longitude
    8
    ;; float64 _seed_latitude
    8
    ;; float64[] _longitude
    (* 8    (length _longitude)) 4
    ;; float64[] _latitude
    (* 8    (length _latitude)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _placemark_type
       (write-long (length _placemark_type) s) (princ _placemark_type s)
     ;; float64 _seed_longitude
       (sys::poke _seed_longitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _seed_latitude
       (sys::poke _seed_latitude (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64[] _longitude
     (write-long (length _longitude) s)
     (dotimes (i (length _longitude))
       (sys::poke (elt _longitude i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _latitude
     (write-long (length _latitude) s)
     (dotimes (i (length _latitude))
       (sys::poke (elt _latitude i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _placemark_type
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _placemark_type (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float64 _seed_longitude
     (setq _seed_longitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _seed_latitude
     (setq _seed_latitude (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64[] _longitude
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _longitude (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _longitude i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _latitude
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _latitude (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _latitude i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get qtnp::Coordinates :md5sum-) "0c53d7b4e0233648a057076b6c290607")
(setf (get qtnp::Coordinates :datatype-) "qtnp/Coordinates")
(setf (get qtnp::Coordinates :definition-)
      "string placemark_type
float64 seed_longitude
float64 seed_latitude
float64[] longitude
float64[] latitude

")



(provide :qtnp/Coordinates "0c53d7b4e0233648a057076b6c290607")


