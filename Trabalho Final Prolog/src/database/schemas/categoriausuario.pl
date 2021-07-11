:- module(categoriausuario, 
		  [
			  categoriausuario/2
		  ]).

:- use_module(library(persistency)).

:- persistent categoriausuario(codigo: positive_integer,
					  descricao: text).

arquivo_da_tabela(FileName):-
	db_attach(FileName, []).

create(Descricao):-
	   must_be(text, Descricao),

	   with_mutex(categoriausuario, (
		   		  primarykey:primarykey(categoriausuario, Codigo),
				  assert_categoriausuario(Codigo, Descricao),
				  primarykey:increment(categoriausuario))).
				  
remove(Codigo):-
	categoriausuario:categoriausuario(Codigo, _),
	with_mutex(categoriausuario, retractall_categoriausuario(Codigo, _)).


update(Codigo, Descricao):-
	must_be(positive_integer, Codigo),
	must_be(text, Descricao),

	categoriausuario:categoriausuario(Codigo, _),
	with_mutex(categoriausuario, 
			   (retractall_categoriausuario(Codigo, _),
			   assert_categoriausuario(Codigo, Descricao))).



sincroniza :-
    db_sync(gc(always)).
