;; Auto-generated. Do not edit!


(when (boundp 'qtnp::Placemarks)
  (if (not (find-package "QTNP"))
    (make-package "QTNP"))
  (shadow 'Placemarks (find-package "QTNP")))
(unless (find-package "QTNP::PLACEMARKS")
  (make-package "QTNP::PLACEMARKS"))

(in-package "ROS")
;;//! \htmlinclude Placemarks.msg.html


(defclass qtnp::Placemarks
  :super ros::object
  :slots (_placemarks ))

(defmethod qtnp::Placemarks
  (:init
   (&key
    ((:placemarks __placemarks) (let (r) (dotimes (i 0) (push (instance qtnp::Coordinates :init) r)) r))
    )
   (send-super :init)
   (setq _placemarks __placemarks)
   self)
  (:placemarks
   (&rest __placemarks)
   (if (keywordp (car __placemarks))
       (send* _placemarks __placemarks)
     (progn
       (if __placemarks (setq _placemarks (car __placemarks)))
       _placemarks)))
  (:serialization-length
   ()
   (+
    ;; qtnp/Coordinates[] _placemarks
    (apply #'+ (send-all _placemarks :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; qtnp/Coordinates[] _placemarks
     (write-long (length _placemarks) s)
     (dolist (elem _placemarks)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; qtnp/Coordinates[] _placemarks
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _placemarks (let (r) (dotimes (i n) (push (instance qtnp::Coordinates :init) r)) r))
     (dolist (elem- _placemarks)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get qtnp::Placemarks :md5sum-) "d412150a28aefbf6a830287329e8685d")
(setf (get qtnp::Placemarks :datatype-) "qtnp/Placemarks")
(setf (get qtnp::Placemarks :definition-)
      "qtnp/Coordinates[] placemarks 

================================================================================
MSG: qtnp/Coordinates
string placemark_type
float64 seed_longitude
float64 seed_latitude
float64[] longitude
float64[] latitude

")



(provide :qtnp/Placemarks "d412150a28aefbf6a830287329e8685d")


