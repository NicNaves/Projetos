:- module(aviso, 
		  [
            aviso/4
		  ]).

:- use_module(library(persistency)).

:- persistent aviso(codigo: positive_integer,
					  de: text,
					  ate: text,
					  descricao: text).

arquivo_da_tabela(FileName):-
	db_attach(FileName, []).

create(DataDe, DataAte, Descricao):-
	   must_be(text, DataDe),
	   must_be(text, DataAte),
	   must_be(text, Descricao),
	   with_mutex(aviso, (
		   		  primarykey:primarykey(aviso, Codigo),
				  assert_aviso(Codigo, DataDe, DataAte, Descricao),
				  primarykey:increment(aviso))).
				  
remove(Codigo):-
	must_be(positive_integer, Codigo),
	aviso:aviso(Codigo, _, _, _),
	with_mutex(aviso, retractall_aviso(Codigo, _, _, _)).


update(Codigo, DataDe, DataAte, Descricao):-
	must_be(positive_integer, Codigo),
	must_be(text, DataDe),
	must_be(text, DataAte),
	must_be(text, Descricao),

	aviso:aviso(Codigo, _, _, _),
	with_mutex(aviso, 
			   (retractall_aviso(Codigo, _, _, _),
			   assert_aviso(Codigo, DataDe, DataAte, Descricao))).

sincroniza :-
    db_sync(gc(always)).
