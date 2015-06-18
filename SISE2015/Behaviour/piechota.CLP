(defglobal ?*Decision* = NONE)
(defglobal ?*Target* = 0)

(defrule FindCurrentNode
	(declare (salience 110))

	(CurrentPlayer ?cPlayer)
	(NodeDistance ?node ?nPlayer ?distance)

	(test (eq (mod ?cPlayer 2) ?nPlayer))
	(test (eq ?distance 0))
	=>
	(assert (CurrentNode ?node))
)
(defrule InitNodes
	(declare (salience 105))
	=>
	(assert (HuntNode 0 20))
)
(defrule FindNearesNodes 
	(declare (salience 100))

	(CurrentPlayer ?cPlayer)
	(CurrentNode ?node)
	(NodeNeighbor ?nNode ?neighbor)
	(NodeDistance ?dNode ?dPlayer ?distance)

	?hunt <- (HuntNode ?hNode ?hDistance)	

	(test (eq ?node ?nNode))
	(test (eq ?neighbor ?dNode))
	(test (not (eq (mod ?cPlayer 2) ?dPlayer)))
	(test (< ?distance ?hDistance))
	=>
	(retract ?hunt)
	(assert (HuntNode ?neighbor ?distance))
)

(defrule ReturnNode
	(declare (salience 60))

	(HuntNode ?hNode ?hDistance)
	=>
	(bind ?*Target* ?hNode)
	(bind ?*Decision* MOVE)	
)
(defrule ShootTest
	(declare (salience 50))
	
	(HuntNode ?hNode ?hDistance)	
	(test (< ?hDistance 1))
	=>
	(bind ?*Decision* SHOOT)	
)