:- module(usuarios, 
		  [
			  %Predicados para o Front-End
			  usuarios/2,
			  usuarios_create_front/2,
			  usuarios_edit_back/3,
			  usuarios_delete_back/3,

			  %Predicados para o Back-End
			  usuarios_index/2,
			  usuarios_create_back/2,
			  usuarios_edit_front/3
		  ]).

:- use_module(library(http/thread_httpd)).
:- use_module(library(http/http_dispatch)).
:- use_module(library(http/html_write)).
:- use_module(library(http/http_server_files)).
:- use_module(library(http/http_client)).
:- use_module(library(http/http_json)).
:- use_module(library(http/json)).
:- use_module(library(http/json_convert)).
:- use_module(library(http/http_parameters)).

tratarJSON2Clientes([], []):-!.
tratarJSON2Clientes([[Id, Cliente_Codigo, CategoriaUsuarioCodigo, Login, Senha, Nome]|Xs], [Y|Ys]):-
Y = json([id=Id,cliente_codigo=Cliente_Codigo,categoria_usuario=CategoriaUsuarioCodigo, login=Login, senha=Senha, nome=Nome]),
tratarJSON2Clientes(Xs, Ys).

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

usuarios_index(get, _Pedido):-
	findall([Id, Cliente_Codigo, CategoriaUsuarioCodigo, Login, Senha, Nome], usuario:usuario(Id, Cliente_Codigo, CategoriaUsuarioCodigo, Login, Senha, Nome), Lista),
	tratarJSON2Clientes(Lista, JSONOut),
	reply_json(JSONOut).

usuarios_create_back(post, Pedido):-
	catch(http_parameters(Pedido, [
		nome(Nome, [string]),
		login(Login, [string]),
		password(Senha, [string]),
		categoria(Categoria, [integer]),
		idcliente(Id_Cliente, [integer])
	]), _E, fail), 
	usuario:create(Categoria, Id_Cliente, Login, Senha, Nome), !,
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/usuarios/cadastrousuariosuccess.html', CadastroUsuarioSuccess, []),
	reply_html_page(Head, [header(Header), content(CadastroUsuarioSuccess)]).

usuarios_create_back(post, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/usuarios/cadastrousuariofail.html', CadastroUsuarioFail, []),
	reply_html_page(Head, [header(Header), content(CadastroUsuarioFail)]).

usuarios_edit_back(put, _Id, Pedido):-
	http_read_json(Pedido, json(JsonIn)),
	tratarJSON(JsonIn, [Id, Nome, Login, Senha, Categoria, Id_Cliente]),
	atom_number(Id, IdInteger),
	atom_number(Categoria, CategoriaInteger),
	atom_number(Id_Cliente, IdClienteInteger),
	usuario:update(IdInteger, IdClienteInteger, CategoriaInteger, Login, Senha, Nome),
	throw(http_reply(no_content)).

usuarios_delete_back(delete, AtomId, _Pedido):-
	atom_number(AtomId, Id),
	!,
	usuario:remove(Id),
	throw(http_reply(no_content)),
	http_redirect(moved, root(usuarios)).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

usuarios(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/usuarios/usuarios.html', Usuarios, []),
	reply_html_page(Head, [header(Header), content(Usuarios)]).

usuarios_create_front(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/usuarios/cadastrousuario.html', CadastroUsuario, []),
	reply_html_page(Head, [header(Header), content(CadastroUsuario)]).

usuarios_edit_front(get, _Id, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/usuarios/editarusuario.html', EditarUsuario, []),
	reply_html_page(Head, [header(Header), content(EditarUsuario)]).