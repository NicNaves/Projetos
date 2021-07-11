:- module(cliente, 
		  [
			  cliente/13
		  ]).

:- use_module(library(persistency)).

:- persistent cliente(seq_cliente: positive_integer,
					  nome: text,
					  dt_nascimento: text,
					  sexo: text,
					  profissao: text,
                      endereco: text,
                      cep  : text,
                      cidade: text,
                      bairro: text,
                      telefone: text,
                      estado: text,
                      email: text,
                      cpf: text).

arquivo_da_tabela(FileName):-
	db_attach(FileName, []).

create(Nome, Dt_nascimento, Sexo, Profissao, Endereco, Cep, Cidade, Bairro, Telefone, Estado, Email, Cpf):-
    must_be(text, Nome),
    must_be(text, Dt_nascimento),
	must_be(text, Sexo),
	must_be(text, Profissao),
	must_be(text, Endereco),
	must_be(text, Cep),
	must_be(text, Cidade),
	must_be(text, Bairro),
	must_be(text, Telefone),
	must_be(text, Estado),
	must_be(text, Email),
	must_be(text, Cpf),
	with_mutex(cliente, (
				primarykey:primarykey(cliente, Seq_cliente),
				assert_cliente(Seq_cliente, Nome, Dt_nascimento, Sexo, Profissao, Endereco, Cep, Cidade, Bairro, Telefone, Estado, Email, Cpf),
				primarykey:increment(cliente))).

remove(Seq_cliente):-
	cliente:cliente(Seq_cliente, _, _, _, _, _, _, _, _, _, _, _, _),
	with_mutex(cliente, retractall_cliente(Seq_cliente, _, _, _, _, _, _, _, _, _, _,_, _)).


update(Seq_cliente, Nome, Dt_nascimento, Sexo, Profissao, Endereco, Cep, Cidade, Bairro, Telefone, Estado, Email, Cpf):-
	must_be(positive_integer, Seq_cliente),
    must_be(text, Nome),
    must_be(text, Dt_nascimento),
	must_be(atom, Sexo),
	must_be(text, Profissao),
	must_be(text, Endereco),
	must_be(text, Cep),
	must_be(text, Cidade),
	must_be(text, Bairro),
	must_be(text, Telefone),
	must_be(atom, Estado),
	must_be(text, Email),
	must_be(text, Cpf),
	cliente:cliente(Seq_cliente, _, _, _, _, _, _, _, _, _, _, _, _),
	with_mutex(cliente, 
			   (retractall_cliente(Seq_cliente, _, _, _, _, _, _, _, _, _, _, _, _),
			    assert_cliente(Seq_cliente, Nome, Dt_nascimento, Sexo, Profissao, Endereco, Cep, Cidade, Bairro, Telefone, Estado, Email, Cpf))).


sincroniza :-
    db_sync(gc(always)).
				  