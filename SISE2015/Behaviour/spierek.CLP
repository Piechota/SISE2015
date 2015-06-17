;test assertion
(defrule FindCurrentNode "Combine Clients and Shipments into Orders"
	(CurrentPlayer ?cPlayerID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)
	(test (eq ?cPlayerID ?nPlayerID))
	(test (eq ?distance 0))
	=>
	(assert (CurrentNode ?nodeID))
)