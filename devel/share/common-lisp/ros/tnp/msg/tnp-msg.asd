
(cl:in-package :asdf)

(defsystem "tnp-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Coordinates" :depends-on ("_package_Coordinates"))
    (:file "_package_Coordinates" :depends-on ("_package"))
    (:file "InitialCoordinates" :depends-on ("_package_InitialCoordinates"))
    (:file "_package_InitialCoordinates" :depends-on ("_package"))
    (:file "Placemarks" :depends-on ("_package_Placemarks"))
    (:file "_package_Placemarks" :depends-on ("_package"))
  ))