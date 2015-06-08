;name, surname, ID
(deffacts Clients
	(Client Jan Kowalski 1)
	(Client Marcin Wawoz 2)
	(Client Jan Kowalski 3)
	(Client Adam Temp 5)
	(Client Bartlomiej Test 6)
)

;name, ID
(deffacts Shipments
	(Shipment Nails 1)
	(Shipment Hammers 2)
	(Shipment Screws 3)
	(Shipment Paint 4)
	(Shipment Wood 5)
)

;test assertion
(defrule assertOrders "Combine Clients and Shipments into Orders"
	(Client ?cName ?cSurname ?cID)
	(Shipment ?sName ?sID)
	(test (eq ?cID ?sID))
	=>
	(assert (Order ?cName ?sName))
)