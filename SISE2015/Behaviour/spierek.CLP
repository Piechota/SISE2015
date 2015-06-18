;USEFUL INFO
	; salience - determines rule priority; higher priority = will be fired earlier
	; ?variable <- fact syntax = assigning a fact to a variable for retracting / modifying
	; test has several versions, with "eq", "<", ">", etc.

;GLOBAL VARIABLES
(defglobal ?*Decision* = NONE)
(defglobal ?*Target* = 0)

;RULES
(defrule FindCurrentNode "Finds the ID of the current player's node, based on distance"
	(declare (salience 100))

	(CurrentPlayer ?cPlayerID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)

	(test (eq ?cPlayerID ?nPlayerID))
	(test (eq ?distance 0))
	=>
	(assert (CurrentNode ?nodeID))
)

(defrule InitNodeSearch
	(declare (salience 80))

	(not (ClosestNode ?$))
	=>
	(assert (ClosestNode 0 20))
	(assert (FurthestNode 0 0))
)

(defrule FindClosestNode "Finds the ID of a node closest to any enemy player"
	(declare (salience 70))

	(CurrentPlayer ?cPlayerID)
	(CurrentNode ?cNodeID)
	(NodeNeighbor ?nNodeID ?neighborID)
	(NodeDistance ?dNodeID ?dPlayerID ?distance)
	?closest <- (ClosestNode ?closestID ?closestDistance)

	(test (eq ?cNodeID ?nNodeID))
	(test (eq ?neighborID ?dNodeID))
	(test (not (eq ?cPlayerID ?dPlayerID)))
	(test (> ?closestDistance ?distance))
	=>
	(retract ?closest)
	(assert (ClosestNode ?neighborID ?distance))
)

(defrule FindFurthestNode "Finds the ID of a node furthest from any enemy players"
	(declare (salience 60))
	
	(CurrentPlayer ?cPlayerID)
	(CurrentNode ?cNodeID)
	(NodeNeighbor ?nNodeID ?neighborID)
	(NodeDistance ?dNodeID ?dPlayerID ?distance)
	?furthest <- (FurthestNode ?furthestID ?furthestDistance)

	(test (eq ?cNodeID ?nNodeID))
	(test (eq ?neighborID ?dNodeID))
	(test (not (eq ?cPlayerID ?dPlayerID)))
	(test (< ?furthestDistance ?distance))
	=>
	(retract ?furthest)
	(assert (FurthestNode ?neighborID ?distance))
)

(defrule DecideEscape "First, decide on running away"
	(declare (salience 50))

	(FurthestNode ?nodeID ?distance)
	
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)

(defrule DecideShoot "... but if the enemy is within range - shoot"
	(declare (salience 40))

	(ClosestNode ?nodeID ?distance)

	(test (<= ?distance 1))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* SHOOT)
)

(defrule DecideMoveTowards "If the enemy is further - move towards"
	(declare (salience 30))

	(ClosestNode ?nodeID ?distance)

	(test (>= ?distance 2))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)