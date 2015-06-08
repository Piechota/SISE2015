(deffacts Student "Student Info"
	(Student Adam 24 M)
	(Student Rob 19 M)
	(Student Mark 22 M)
	(Student Anya 23 F)
	(Student Martha 21 F)
)

(printout t "Female students:" crlf)
(defrule checkFemale "Print out all female students"
	(Student ?SName ?SAge ?SGender)
	(test (eq ?SGender F))
	=>
	(printout t ?SName " " ?SAge " " ?SGender crlf)
)

(printout t "Students over age 21:" crlf)
(defrule checkAge "Checks if the student's age is over 21"
	(Student ?SName ?SAge ?SGender)
	(test (> ?SAge 21))
	=>
	(printout t ?SName " " ?SAge crlf)
)