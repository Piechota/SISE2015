;test assertion
(defrule assertOrders "Combine Clients and Shipments into Orders"
	(NodeA ?nAID)
	(NodeB ?nBID)
	(test (eq ?nAID ?nBID))
	=>
	(assert (CombinedNode ?nAID ?nBID))
)

(deffunction Add (?a ?b)
	(+ ?a ?b)
)

(deffunction Hypotenuse (?a ?b)
	(sqrt(+ (* ?a ?a) (* ?b ?b)))	
)

(deffunction ReturnSum ()
	(+ 5 10)	
)