;test assertion
(defrule FindCurrentNode "Finds the ID of the current player's node, based on distance"
	(CurrentPlayer ?cPlayerID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)

	(test (eq ?cPlayerID ?nPlayerID))
	(test (eq ?distance 0))
	=>
	(assert (CurrentNode ?nodeID))
)

(defrule FindNearestNodes "Finds the IDs of nearby nodes, based on distance"
	(CurrentPlayer ?cPlayerID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)

	(test (eq ?cPlayerID ?nPlayerID))
	(test (eq ?distance 1))
	=>
	(assert (NearestNode ?nodeID))
)

(defrule InitBestNodeSearch
	(not (BestNode ?))
	=>
	(assert (BestNode 0 20))
)

(defrule FindBestNode "Finds the ID of a node closest to the enemy player"
	(NearestNode ?nearestID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)
	?best <- (BestNode ?bestID ?bestDistance)

	(test (eq ?nearestID ?nodeID))
	(test (> ?bestDistance ?distance))
	=>
	(retract ?best)
	(assert (BestNode ?nodeID ?distance))
)