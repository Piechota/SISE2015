;USEFUL INFO
	; salience - determines rule priority; higher priority = will be fired earlier
	; ?variable <- fact syntax = assigning a fact to a variable for retracting / modifying
	; test has several versions, with "eq", "<", ">", etc.

;GLOBALS
(defglobal ?*Decision* = NONE)
(defglobal ?*Target* = 0)
(defglobal ?*NeighbourCount* = 0)

;RULES
(defrule GetMyNode "Finds the ID of the current player's node, based on distance"
	(declare (salience 100))

	(CurrentPlayer ?cPlayerID)
	(NodeDistance ?nodeID ?nPlayerID ?distance)

	(test (eq (mod ?cPlayerID 2) ?nPlayerID))
	(test (eq ?distance 0))
	=>
	(assert (MyNode ?nodeID))
)

(defrule GetNeighbourCount
	(declare (salience 110))
	
	(MyNode ?nodeID)
	(NodeNeighbor ?nNodeID ?neighborID)	
	
	(test (eq ?nodeID ?neighborID))
	=>
	(bind ?*NeighbourCount* (+ ?*NeighbourCount* 1))
)

(defrule InitNodeSearch
	(declare (salience 100))

	(not (NearestNode ?$))
	=>
	(assert (NearestNode 0 20))
	(assert (FurthestNode 0 0))
)

(defrule GetDistanceToEnemy
	(declare (salience 90))
	
	(MyNode ?nodeID)
	(NodeDistance ?dNodeID ?dPlayerID ?distance)
	(CurrentPlayer ?cPlayerID)
	
	(test (eq ?dNodeID ?nodeID))
	(test (not (eq (mod ?cPlayerID 2) (mod ?dPlayerID 2))))
	=>
	(assert (EnemyDistance ?distance))
)

(defrule FindNearestNode "Finds the ID of a node closest to any enemy player"
	(declare (salience 80))

	(CurrentPlayer ?cPlayerID)
	(MyNode ?cNodeID)
	(NodeNeighbor ?nNodeID ?neighborID)
	(NodeDistance ?dNodeID ?dPlayerID ?distance)
	?closest <- (NearestNode ?closestID ?closestDistance)

	(test (eq ?cNodeID ?nNodeID))
	(test (eq ?neighborID ?dNodeID))
	(test (not (eq (mod ?cPlayerID 2) ?dPlayerID)))
	(test (> ?closestDistance ?distance))
	=>
	(retract ?closest)
	(assert (NearestNode ?neighborID ?distance))
)

(defrule FindDistandNode "Finds the ID of a node furthest from any enemy players"
	(declare (salience 70))
	
	(CurrentPlayer ?cPlayerID)
	(MyNode ?cNodeID)
	(NodeNeighbor ?nNodeID ?neighborID)
	(NodeDistance ?dNodeID ?dPlayerID ?distance)
	?furthest <- (FurthestNode ?furthestID ?furthestDistance)

	(test (eq ?cNodeID ?nNodeID))
	(test (eq ?neighborID ?dNodeID))
	(test (not (eq (mod ?cPlayerID 2) ?dPlayerID)))
	(test (< ?furthestDistance ?distance))
	=>
	(retract ?furthest)
	(assert (FurthestNode ?neighborID ?distance))
)

(defrule IWantRandomNode "Find me a random node neighbour, but not the closest"
	(declare (salience 60))
	
	(MyNode ?cNodeID)
	(NodeNeighbor ?nNodeID ?neighborID)
	(NearestNode ?closestID ?closestDistance)
	(FurthestNode ?furthestID ?furthestDistance)
	
	(not (RandomNode ?$))
	(test (eq ?cNodeID ?nNodeID))
	(test (not (eq ?nNodeID ?furthestID)))
	=>
	(assert (RandomNode ?nNodeID))
)

(defrule DecideFlee "First, decide on running away"
	(declare (salience 50)) 

	(FurthestNode ?nodeID ?distance)
	
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)

(defrule DecidePoke "... but if the enemy is within range - shoot"
	(declare (salience 40))

	(NearestNode ?nodeID ?distance)
	
	(test (<= ?distance 1))
	(test (<= ?*NeighbourCount* 3))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* SHOOT)
)

(defrule DecideHunt "If the enemy is further - move towards"
	(declare (salience 30))

	(NearestNode ?nodeID ?distance)

	(test (>= ?distance 2))
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* MOVE)
)

(defrule MyRandom "not really a random, but whatever"
	(declare (salience 20))
	
	(NearestNode ?nodeID ?ndistance)
	(EnemyDistance ?edistance)
	
	(test (<= ?*NeighbourCount* 3))
	(eq ?edistance 2)
	=>
	(bind ?*Target* ?nodeID)
	(bind ?*Decision* SHOOT)
)