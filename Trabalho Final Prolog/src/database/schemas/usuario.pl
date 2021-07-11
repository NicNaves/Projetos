:- module(usuario, 
		  [
			  usuario/6
		  ]).

:- use_module(library(persistency)).

/*Para Gestores da Clínica, o cliente_codigo sempre será 1 */
:- persistent usuario(codigo: positive_integer,
					  cliente_codigo: positive_integer,
					  categoria_usuario_codigo: positive_integer,
					  login: text,
					  senha: text,
					  nome: text).

arquivo_da_tabela(FileName):-
	db_attach(FileName, []).

create(Usuario_Categoria, Cliente_Codigo, Login, Senha, Nome):-
	   must_be(positive_integer, Usuario_Categoria),
	   must_be(positive_integer, Cliente_Codigo),
	   must_be(text, Login),
	   must_be(text, Senha),
	   must_be(text, Nome),
	   categoriausuario:categoriausuario(Usuario_Categoria, _),
	   \+ usuario:usuario(_, _, _, Login, _, _),
	   cliente:cliente(Cliente_Codigo, _, _, _, _, _, _, _, _, _, _,_, _),
	   with_mutex(usuario, (
		   		  primarykey:primarykey(usuario, Codigo),
				  assert_usuario(Codigo, Cliente_Codigo, Usuario_Categoria, Login, Senha, Nome),
				  primarykey:increment(usuario))).
				  
remove(Codigo):-
	must_be(positive_integer, Codigo), !,
	usuario:usuario(Codigo, _, _, _, _, _),
	with_mutex(usuario, retractall_usuario(Codigo, _, _, _, _, _)).

remove(Login):-
	must_be(atom, Login),
	usuario:usuario(_, _, _, Login, _, _), !,
	with_mutex(usuario, retractall_usuario(_, _, _, Login, _, _)).

update(Codigo, Cliente_Codigo, Usuario_Categoria, Login, Senha, Nome):-
	must_be(positive_integer, Codigo),
	must_be(positive_integer, Usuario_Categoria),
	must_be(positive_integer, Cliente_Codigo),
	usuario:usuario(Codigo, _, _, _, _, _),
	categoriausuario:categoriausuario(Usuario_Categoria, _),
	cliente:cliente(Cliente_Codigo, _, _, _, _, _, _, _, _, _, _,_, _),
	with_mutex(usuario, 
			   (retractall_usuario(Codigo, _, _, _, _, _),
			    assert_usuario(Codigo, Cliente_Codigo, Usuario_Categoria, Login, Senha, Nome))).

sincroniza :-
    db_sync(gc(always)).
