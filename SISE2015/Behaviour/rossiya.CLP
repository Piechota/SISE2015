(defglobal ?*Decision* = NONE) ;Decision type: MOVE, SHOOT, SUICIDE
(defglobal ?*Target* = 0) ;ID of targeted node

(defrule FindMyNodeID
	(declare (salience 100))

	(CurrentPlayer ?currentPlayerID)
	(NodeDistance ?nodeID ?nodePlayerID ?distance)

	(test (eq (mod ?currentPlayerID 2) ?nodePlayerID))
	(test (eq ?distance 0))
	=>
	(assert (CurrentNode ?nodeID))
)

(defrule InitializeNodeSearch
	(declare (salience 90))

	(not (ClosestNode ?$))
	=>
	(assert (ClosestNode 0 20))
	(assert (FurthestNode 0 0))
)

(defrule FindNodeIDClosestToEnemy
	(declare (salience 80))

	(CurrentPlayer ?currentPlayerID)
	(CurrentNode ?currentNodeID)
	(NodeNeighbor ?nNodeID ?neighborID)
	(NodeDistance ?dNodeID ?dPlayerID ?distance)
	?closest <- (ClosestNode ?closestID ?closestDistance)

	(test (eq ?currentNodeID ?nNodeID))
	(test (eq ?neighborID ?dNodeID))
	(test (not (eq (mod ?currentPlayerID 2) ?dPlayerID)))
	(test (> ?closestDistance ?distance))
	=>
	(retract ?closest)
	(assert (ClosestNode ?neighborID ?distance))
)

(defrule FindNodeIDFurthestFromEnemy
	(declare (salience 70))
	
	(CurrentPlayer ?currentPlayerID)
	(CurrentNode ?currentNodeID)
	(NodeNeighbor ?nNodeID ?neighborID)
	(NodeDistance ?dNodeID ?dPlayerID ?distance)
	?furthest <- (FurthestNode ?furthestID ?furthestDistance)

	(test (eq ?currentNodeID ?nNodeID))
	(test (eq ?neighborID ?dNodeID))
	(test (not (eq (mod ?currentPlayerID 2) ?dPlayerID)))
	(test (< ?furthestDistance ?distance))
	=>
	(retract ?furthest)
	(assert (FurthestNode ?neighborID ?distance))
)

(defrule ShootEnemy
	(declare (salience 50))

	(ClosestNode ?nodeID ?distance)

	(test (<= ?distance 3))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* SHOOT)
)

(defrule ChaseEnemy
	(declare (salience 40))

	(ClosestNode ?nodeID ?distance)

	(test (>= ?distance 4))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)