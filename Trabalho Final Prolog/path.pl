:- multifile user:file_search_path/2.

user:file_search_path(src, './src').
user:file_search_path(database, src(database)).
user:file_search_path(routes, src(routes)).
user:file_search_path(schemas, database(schemas)).
user:file_search_path(tables, database(tables)).
user:file_search_path(static, './static').
user:file_search_path(images, static(images)).
user:file_search_path(fixed, static(fixed)).
user:file_search_path(css, './static/css').