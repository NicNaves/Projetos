:- module(primarykey, 
		 [
			 primarykey/2
		 ]).

:- use_module(library(persistency)).

:- persistent primarykey(tabela:atom,
						 primarykey: positive_integer).

arquivo_da_tabela(FileName):-
	db_attach(FileName, []).

create(Tabela):-
	with_mutex(primarykey,
			   ( \+ primarykey:primarykey(Tabela, _), 
			     assert_primarykey(Tabela, 1))).

remove(Tabela):-
	with_mutex(primarykey,
			  (primarykey:primarykey(Tabela, _),
	           retractall_primarykey(Tabela, _))).

update(Tabela, PrimaryKey):-
	primarykey:primarykey(Tabela, _),
	with_mutex(primarykey,
			  ( retractall_primarykey(Tabela, _),
			    assert_primarykey(Tabela, PrimaryKey))).

increment(Tabela):-
	with_mutex(primarykey, 
		       ( primarykey:primarykey(Tabela, PrimaryKey),
			     NewPrimaryKey is PrimaryKey + 1,
			     update(Tabela, NewPrimaryKey))).
