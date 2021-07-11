:- load_files(
		[path, src(database), routes(clienteroute), 
							  routes(tratamentosroute),
							  routes(agendaroute),
							  routes(usuarioroute),
							  routes(avisosroute),
							  routes(loginroute)], [if(not_loaded), silent(true)]
	).

tratarJSON([],[]):-!.
tratarJSON([X|Xs], [Y|Ys]):-
	(X)=..[_,_,Valor],
	Y = Valor,
	tratarJSON(Xs, Ys).

:- use_module(library(http/thread_httpd)).
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/html_write)).
:- use_module(library(http/http_server_files)).
:- use_module(library(http/http_client)).
:- use_module(library(http/http_json)).
:- use_module(library(http/json)).
:- use_module(library(http/json_convert)).
:- use_module(library(http/http_parameters)).

server:-
	http_server(http_dispatch, [port(8000)]).

:- initialization(server).

/**********************************************************************************/
/****************************** RECURSOS ******************************************/
/**********************************************************************************/

http:location(images, root(images), []).

:- http_handler(css(.), serve_files_in_directory(css), [prefix]).
:- http_handler(images(.), serve_files_in_directory(images), [prefix]).

/**********************************************************************************/
/****************************** HOME **********************************************/
/**********************************************************************************/

:- http_handler(root(home), home, []).

home(_Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/home.html', Home, []),
	reply_html_page(Head, [header(Header), content(Home)]).








/**********************************************************************************/
/****************************** CLIENTES ******************************************/
/**********************************************************************************/

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

:- http_handler(root(api/clientes/index), clientes_index(get), [method(get), methods([get])]).
:- http_handler(root(api/clientes/criar), clientes_create_back(post), [method(post), methods([post])]).
:- http_handler(root(api/clientes/editar/Id), clientes_edit_back(put, Id), [method(put), methods([put])]).
:- http_handler(root(api/clientes/deletar/Id), clientes_delete_back(delete, Id), [method(delete), methods([delete])]).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

:- http_handler(root(clientes), clientes(get), [method(get), methods([get])]).
:- http_handler(root(clientes/editar/Id), clientes_edit_front(get, Id), [method(get), methods([get])]).
:- http_handler(root(clientes/criar), clientes_create_front(get), [method(get), methods([get])]).







/**********************************************************************************/
/****************************** TRATAMENTOS ***************************************/
/**********************************************************************************/

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

:- http_handler(root(api/tratamentos/index), tratamentos_index(get), [method(get), methods([get])]).
:- http_handler(root(api/tratamentos/criar), tratamentos_create_back(post), [method(post), methods([post])]).
:- http_handler(root(api/tratamentos/editar/Id), tratamentos_edit_back(put, Id), [method(put), methods([put])]).
:- http_handler(root(api/tratamentos/deletar/Id), tratamentos_delete_back(delete, Id), [method(delete), methods([delete])]).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

:- http_handler(root(tratamentos), tratamentos(get), [method(get), methods([get])]).
:- http_handler(root(tratamentos/criar), tratamentos_create_front(get), [method(get), methods([get])]).
:- http_handler(root(tratamentos/editar/Id), tratamentos_edit_front(get, Id), [method(get), methods([get])]).








/**********************************************************************************/
/****************************** AGENDA ********************************************/
/**********************************************************************************/

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

:- http_handler(root(api/agendas/index), agendas_index(get), [method(get), methods([get])]).
:- http_handler(root(api/agendas/criar), agendas_create_back(post), [method(post), methods([post])]).
:- http_handler(root(api/agendas/editar/Id), agendas_edit_back(put, Id), [method(put), methods([put])]).
:- http_handler(root(api/agendas/deletar/Id), agendas_delete_back(delete, Id), [method(delete), methods([delete])]).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

:- http_handler(root(agendas), agendas(get), [method(get), methods([get])]).
:- http_handler(root(agendas/criar), agendas_create_front(get), [method(get), methods([get])]).
:- http_handler(root(agendas/editar/Id), agendas_edit_front(get, Id), [method(get), methods([get])]).









/**********************************************************************************/
/****************************** USUARIOS ******************************************/
/**********************************************************************************/

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

:- http_handler(root(api/usuarios/index), usuarios_index(get), [method(get), methods([get])]).
:- http_handler(root(api/usuarios/criar), usuarios_create_back(post), [method(post), methods([post])]).
:- http_handler(root(api/usuarios/editar/Id), usuarios_edit_back(put, Id), [method(put), methods([put])]).
:- http_handler(root(api/usuarios/deletar/Id), usuarios_delete_back(delete, Id), [method(delete), methods([delete])]).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

:- http_handler(root(usuarios), usuarios(get), [method(get), methods([get])]).
:- http_handler(root(usuarios/criar), usuarios_create_front(get), [method(get), methods([get])]).
:- http_handler(root(usuarios/editar/Id), usuarios_edit_front(get, Id), [method(get), methods([get])]).









/**********************************************************************************/
/****************************** AVISOS ********************************************/
/**********************************************************************************/

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

:- http_handler(root(api/avisos/index), avisos_index(get), [method(get), methods([get])]).
:- http_handler(root(api/avisos/criar), avisos_create_back(post), [method(post), methods([post])]).
:- http_handler(root(api/avisos/deletar/Id), avisos_delete_back(delete, Id), [method(delete), methods([delete])]).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

:- http_handler(root(avisos), avisos(get), [method(get), methods([get])]).
:- http_handler(root(avisos/criar), avisos_create_front(get), [method(get), methods([get])]).








/**********************************************************************************/
/****************************** LOGIN ********************************************/
/**********************************************************************************/

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

:- http_handler(root(api/login), login_validate(post), [method(post), methods([post])]).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

:- http_handler(root(.), login(get), [method(get), methods([get])]).