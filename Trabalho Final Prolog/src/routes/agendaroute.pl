:- module(agendas, 
		  [
			  %Predicados para o Front-End
			  agendas/2,
			  agendas_create_front/2,
			  agendas_edit_back/3,
			  agendas_delete_back/3,

			  %Predicados para o Back-End
			  agendas_index/2,
			  agendas_create_back/2,
			  agendas_edit_front/3
		  ]).

tratarJSON2Agendas([], []):-!.
tratarJSON2Agendas([[Id, Data, Horario, Cliente, Telefone, Observacao]|Xs], [Y|Ys]):-
Y = json([id=Id,data=Data,horario=Horario, cliente=Cliente, telefone=Telefone, observacao=Observacao]),
tratarJSON2Agendas(Xs, Ys).

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

agendas_index(get, _Pedido):-
	findall([Id, Data, Horario, Cliente, Telefone, Observacao], agenda:agenda(Id, Horario, Observacao, Data, Telefone, Cliente), Lista),
	tratarJSON2Agendas(Lista, JSONOut),
	reply_json(JSONOut).

agendas_create_back(post, Pedido):-
	catch(http_parameters(Pedido, [
		data(Data, [string]),
		cliente(Cliente, [string]),
		telefone(Telefone, [string]),
		horario(Horario, [string]),
		observacao(Observacao, [string])
	]), _E, fail), !,
	agenda:create(Horario, Observacao, Data, Telefone, Cliente),
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/agendas/cadastroagendasuccess.html', CadastroAgendaSuccess, []),
	reply_html_page(Head, [header(Header), content(CadastroAgendaSuccess)]).

agendas_create_back(post, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/agendas/cadastroagendafail.html', CadastroAgendaFail, []),
	reply_html_page(Head, [header(Header), content(CadastroAgendaFail)]).

agendas_edit_back(put, _Id, Pedido):-
	http_read_json(Pedido, json(JsonIn)),
	tratarJSON(JsonIn, [Id, Data, Cliente, Telefone, Horario, Observacao]),
	atom_number(Id, IdInteger),
	agenda:update(IdInteger, Horario, Observacao, Data, Telefone, Cliente),
	throw(http_reply(no_content)).

agendas_delete_back(delete, AtomId, _Pedido):-
	atom_number(AtomId, Id),
	!,
	agenda:remove(Id),
	throw(http_reply(no_content)),
	http_redirect(moved, root(tratamentos)).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

agendas(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/agendas/agendas.html', Agendas, []),
	reply_html_page(Head, [header(Header), content(Agendas)]).

agendas_create_front(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/agendas/cadastroagenda.html', CriarAgenda, []),
	reply_html_page(Head, [header(Header), content(CriarAgenda)]).

agendas_edit_front(get, _Id, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/agendas/editaragenda.html', EditarAgenda, []),
	reply_html_page(Head, [header(Header), content(EditarAgenda)]).