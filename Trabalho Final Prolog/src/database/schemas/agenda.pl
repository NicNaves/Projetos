:- module(agenda, 
		  [
			  agenda/6
		  ]).

:- use_module(library(persistency)).

:- persistent agenda(seq_agenda: positive_integer,
					  hora: text,
					  observacao: text,
					  data_2: text,
					  telefone: text,
					  cliente: text).

arquivo_da_tabela(FileName):-
	db_attach(FileName, []).

create(Hora, Observacao, Data_2, Telefone, Cliente):-
	   must_be(text, Hora),
	   must_be(text, Observacao),
	   must_be(text, Data_2),
	   must_be(text, Telefone),
	   must_be(text, Cliente),
	   with_mutex(agenda, (
		   		  primarykey:primarykey(agenda, Seq_agenda),
				  assert_agenda(Seq_agenda, Hora, Observacao, Data_2, Telefone, Cliente),
				  primarykey:increment(agenda))).
				  
remove(Seq_agenda):-
	agenda:agenda(Seq_agenda, _, _, _, _, _),
	with_mutex(agenda, retractall_agenda(Seq_agenda, _, _, _, _, _)).


update(Seq_agenda, Hora, Observacao, Data_2, Telefone,Cliente):-
	must_be(positive_integer, Seq_agenda),
	must_be(text, Hora),
	must_be(text, Observacao),
	must_be(text, Data_2),
	must_be(text, Telefone),
	must_be(text, Cliente),
	agenda:agenda(Seq_agenda, _, _, _, _, _),
	with_mutex(agenda, 
			   (retractall_agenda(Seq_agenda, _, _, _, _, _),
			   assert_agenda(Seq_agenda, Hora, Observacao, Data_2, Telefone, Cliente))).



sincroniza :-
    db_sync(gc(always)).
