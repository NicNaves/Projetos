:- module(avisos, 
		  [
			  %Predicados para o Front-End
			  avisos/2,
			  avisos_create_front/2,

			  %Predicados para o Back-End
			  avisos_index/2,
			  avisos_create_back/2,
			  avisos_delete_back/3
		  ]).

tratarJSON2Avisos([], []):-!.
tratarJSON2Avisos([[Id, DataDe, DataAte, Descricao]|Xs], [Y|Ys]):-
Y = json([id=Id,datade=DataDe,dataate=DataAte, descricao=Descricao]),
tratarJSON2Avisos(Xs, Ys).

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

avisos_index(get, _Pedido):-
	findall([Id, DataDe, DataAte, Descricao], aviso:aviso(Id, DataDe, DataAte, Descricao), Lista),
	tratarJSON2Avisos(Lista, JSONOut),
	reply_json(JSONOut).

avisos_create_back(post, Pedido):-
	catch(http_parameters(Pedido, [
		datade(DataDe, [string]),
		dataate(DataAte, [string]),
		descricao(Descricao, [string])
	]), _E, fail), !,
	aviso:create(DataDe, DataAte, Descricao),
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/avisos/cadastroavisosuccess.html', CadastroAvisoSuccess, []),
	reply_html_page(Head, [header(Header), content(CadastroAvisoSuccess)]).

avisos_create_back(post, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/avisos/cadastroavisofail.html', CadastroAvisoFail, []),
	reply_html_page(Head, [header(Header), content(CadastroAvisoFail)]).

avisos_delete_back(delete, AtomId, _Pedido):-
	atom_number(AtomId, Id),
	!,
	aviso:remove(Id),
	throw(http_reply(no_content)),
	http_redirect(moved, root(avisos)).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

avisos(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/avisos/avisos.html', Avisos, []),
	reply_html_page(Head, [header(Header), content(Avisos)]).

avisos_create_front(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/avisos/cadastroaviso.html', CadastroAviso, []),
	reply_html_page(Head, [header(Header), content(CadastroAviso)]).

	