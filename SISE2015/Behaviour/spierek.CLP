;USEFUL INFO
	; salience - determines rule priority; higher priority = will be fired earlier
	; ?variable <- fact syntax = assigning a fact to a variable for retracting / modifying
	; test has several versions, with "eq", "<", ">", etc.

;GLOBAL VARIABLES
(defglobal ?*Decision* = Move)
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

(defrule FindNeighborNodes "Finds the IDs of nearby nodes, based on distance"
	(declare (salience 90))

	(CurrentPlayer ?cPlayerID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)

	(test (eq ?cPlayerID ?nPlayerID))
	(test (eq ?distance 1))
	=>
	(assert (NeighborNode ?nodeID))
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

	(NeighborNode ?neighborID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)
	?closest <- (ClosestNode ?closestID ?closestDistance)

	(test (eq ?neighborID ?nodeID))
	(test (> ?closestDistance ?distance))
	=>
	(retract ?closest)
	(assert (ClosestNode ?nodeID ?distance))
)

(defrule FindFurthestNode "Finds the ID of a node furthest from any enemy players"
	(declare (salience 60))

	(NeighborNode ?neighborID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)
	?furthest <- (FurthestNode ?furthestID ?furthestDistance)

	(test (eq ?neighborID ?nodeID))
	(test (< ?furthestDistance ?distance))
	=>
	(retract ?furthest)
	(assert (FurthestNode ?nodeID ?distance))
)

(defrule DecideShoot "If the enemy is within range - shoot"
	(declare (salience 50))

	(ClosestNode ?nodeID ?distance)
	(not (Decision ?))

	(test (< ?distance 3))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* SHOOT)
	(assert (SHOOTYSHOOTYBANGBANG ?distance))
)

(defrule DecideMoveTowards "If the enemy is further - move towards"
	(declare (salience 40))

	(ClosestNode ?nodeID ?distance)
	(not (Decision ?))

	(test (> ?distance 2))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)

(defrule DecideEscape "Otherwise - step back"
	(declare (salience 30))

	(FurthestNode ?nodeID ?distance)
	(not (Decision ?))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)