:- module(tratamento, 
		  [
            tratamento/4
		  ]).

:- use_module(library(persistency)).

:- persistent tratamento(codigo: positive_integer,
					  nome: text,
					  duracao: text,
					  descricao: text).

arquivo_da_tabela(FileName):-
	db_attach(FileName, []).

create(Nome, Duracao, Descricao):-
	   must_be(text, Nome),
	   must_be(text, Duracao),
       must_be(text, Descricao),
	   with_mutex(tratamento, (
		   		  primarykey:primarykey(tratamento, Codigo),
				  assert_tratamento(Codigo, Nome, Duracao, Descricao),
				  primarykey:increment(tratamento))).
				  
remove(Codigo):-
	tramento:tratamento(Codigo, _, _, _),
	with_mutex(tratamento, retractall_tratamento(Codigo, _, _, _)).


update(Codigo, Nome, Duracao, Descricao):-
	must_be(text, Nome),
    must_be(text, Duracao),
    must_be(text, Descricao),

	tratamento:tratamento(Codigo, _, _, _),
	with_mutex(tratamento, 
			   (retractall_tratamento(Codigo, _, _, _),
			   assert_tratamento(Codigo, Nome, Duracao, Descricao))).



sincroniza :-
    db_sync(gc(always)).
