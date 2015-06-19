(defglobal ?*Decision* = NONE) ;Decision type: MOVE, SHOOT, SUICIDE
(defglobal ?*Target* = 0) ;ID of targeted node

(defrule FindCurrentNode
	(declare (salience 110))

	(CurrentPlayer ?cPlayer)
	(NodeDistance ?node ?nPlayer ?distance)

	(test (eq (mod ?cPlayer 2) ?nPlayer))
	(test (eq ?distance 0))
	=>
	(assert (CurrentNode ?node))
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

(defrule ChaseEnemy
	(declare (salience 40))

	(FurthestNode ?nodeID ?distance)	
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)


(defrule ShootEnemy
	(declare (salience 50))

	(ClosestNode ?nodeID ?distance)

	(test (<= ?distance 1))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* SHOOT)
)

