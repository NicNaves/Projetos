:- module(tratamentos, 
		  [
			  %Predicados para o front-end
			  tratamentos/2,
			  tratamentos_create_front/2,
			  tratamentos_edit_front/3,
			  
			  %Predicados para o back-end
			  tratamentos_index/2,
			  tratamentos_create_back/2,
			  tratamentos_delete_back/3,
			  tratamentos_edit_back/3
		  ]).

tratarJSON2Tratamentos([], []):-!.
tratarJSON2Tratamentos([[Id, Nome, Duracao, Observacao]|Xs], [Y|Ys]):-
	Y = json([id=Id,nome=Nome,duracao=Duracao, observacao=Observacao]),
	tratarJSON2Tratamentos(Xs, Ys).

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

tratamentos_index(get, _Pedido):-
	findall([Id, Nome, Duracao, Observacao], tratamento:tratamento(Id, Nome, Duracao, Observacao), Lista),
	tratarJSON2Tratamentos(Lista, JsonOut),
	reply_json(JsonOut).

tratamentos_create_back(post, Pedido):-
	catch(http_parameters(Pedido, [
		nome(Nome, [string]),
		duracao(Duracao, [string]),
		observacao(Observacao, [string])
	]), _E, fail), !,
	tratamento:create(Nome, Duracao, Observacao),
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/tratamentos/cadastrotratamentosuccess.html', CadastroTratamentoSuccess, []),
	reply_html_page(Head, [header(Header), content(CadastroTratamentoSuccess)]).

tratamentos_create_back(post, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/tratamentos/cadastrotratamentofail.html', CadastroTratamentoFail, []),
	reply_html_page(Head, [header(Header), content(CadastroTratamentoFail)]).

tratamentos_delete_back(delete, AtomId, _Pedido):-
	atom_number(AtomId, Id),
	!,
	tratamento:remove(Id),
	throw(http_reply(no_content)),
	http_redirect(moved, root(tratamentos)).

tratamentos_edit_back(put, _AtomId, Pedido):-
	http_read_json(Pedido, json(JsonIn)),
	tratarJSON(JsonIn, [Id, Nome, Duracao, Observacao]),
	atom_number(Id, IdInteger),
	tratamento:update(IdInteger, Nome, Duracao, Observacao),
	throw(http_reply(no_content)).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

tratamentos(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/tratamentos/tratamentos.html', Tratamentos, []),
	reply_html_page(Head, [header(Header), content(Tratamentos)]).

tratamentos_create_front(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/tratamentos/cadastrotratamento.html', CadastroTratamento, []),
	reply_html_page(Head, [header(Header), content(CadastroTratamento)]).

tratamentos_edit_front(get, _Id,_Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/tratamentos/editartratamento.html', EditarTratamento, []),
	reply_html_page(Head, [header(Header), content(EditarTratamento)]).