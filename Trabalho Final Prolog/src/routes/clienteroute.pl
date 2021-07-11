:- module(clientes, 
		  [
			  %Predicados para o front-end
			  clientes/2,
			  clientes_create_front/2,
			  clientes_edit_front/3,

			  %Predicados para o back-end
			  clientes_index/2,
			  clientes_create_back/2,
			  clientes_delete_back/3,
			  clientes_edit_back/3
			  
		  ]).

tratarJSON2Clientes([], []):-!.
tratarJSON2Clientes([[Id, Nome, Telefone, Email]|Xs], [Y|Ys]):-
Y = json([id=Id,nome=Nome,telefone=Telefone, email=Email]),
tratarJSON2Clientes(Xs, Ys).

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

clientes_index(get, _Pedido):-
	findall([Id, Nome, Telefone, Email], cliente:cliente(Id, Nome, _, _, _, _, _, _, _, Telefone, _, Email, _), Lista),
	tratarJSON2Clientes(Lista, JsonOut),
	reply_json(JsonOut).

clientes_create_back(post, Pedido) :-
	catch(http_parameters(Pedido, [
		nome(Nome, [string]),
		cpf(Cpf, [string]),
		data(DataDeNasc, [string]),
		sexo(Sexo, [string]),
		endereco(Endereco, [string]),
		bairro(Bairro, [string]),
		cidade(Cidade, [string]),
		estado(Estado, [string]),
		cep(Cep, [string]),
		telefone(Telefone, [string]),
		email(Email, [string]),
		profissao(Profissao, [string])
	]), _E, fail), !,
	cliente:create(Nome, DataDeNasc, Sexo, Profissao, Endereco, Cep, Cidade, Bairro, Telefone, Estado, Email, Cpf),
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/clientes/cadastroclientesuccess.html', CadastroCliente, []),
	reply_html_page(Head, [header(Header), content(CadastroCliente)]).

clientes_create_back(post, _Pedido) :-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/clientes/cadastroclientefail.html', CadastroCliente, []),
	reply_html_page(Head, [header(Header), content(CadastroCliente)]).

clientes_delete_back(delete, AtomId, _Pedido):-
	atom_number(AtomId, Id),
	!,
	cliente:remove(Id),
	throw(http_reply(no_content)),
	http_redirect(moved, root(clientes)).

clientes_edit_back(put, _, Pedido):-
	http_read_json(Pedido, json(JsonIn)),
	tratarJSON(JsonIn, [Id, Nome, Cpf, DataDeNasc, Sexo, Endereco, Bairro, Cidade, Estado, Cep, Telefone, Email, Profissao]),
	atom_number(Id, IdInteger),
	cliente:update(IdInteger, Nome, DataDeNasc, Sexo, Profissao, Endereco, Cep, Cidade, Bairro, Telefone, Estado, Email, Cpf),
	throw(http_reply(no_content)).


/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

clientes(get, _Pedido) :-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/clientes/clientes.html', Clientes, []),
	reply_html_page(Head, [header(Header), content(Clientes)]).

clientes_create_front(get, _Pedido) :-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/clientes/cadastrocliente.html', CadastroClientes, []),
	reply_html_page(Head, [header(Header), content(CadastroClientes)]).

clientes_edit_front(get, _, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/fixed/header.html', Header, []),
	load_html('./static/clientes/editarcliente.html', EditarCliente, []),
	reply_html_page(Head, [header(Header), content(EditarCliente)]).