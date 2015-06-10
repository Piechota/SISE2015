;name, surname, ID
(deffacts Clients
	(Client Jan Kowalski 1)
	(Client Marcin Wawoz 2)
)

;name, ID
(deffacts Shipments
	(Shipment Nails 1)
)

;test assertion
(defrule assertOrders "Combine Clients and Shipments into Orders"
	(Client ?cName ?cSurname ?cID)
	(Shipment ?sName ?sID)
	(test (eq ?cID ?sID))
	=>
	(assert (Order ?cName ?sName))
)