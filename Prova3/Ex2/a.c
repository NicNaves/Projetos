
int verifica (char *s) {
    Stack *st;
    st = stack_create (MAX);
    struct chars c;
    int i = 0;
    int result;
    for (i = 0; s[i] != '\0'; ++i) {
        if(s[i] == ']'){
            if(stack_size(st) == 0)
                return -1;
            else{
                stack_top(st, &c);
                if(c.ch != '[')
                    return -1;
                else
                    stack_pop(st);
            }
        }
        else if(s[i] == ')'){
            if(stack_size(st) == 0)
                return -1;
            else{
                stack_top(st, &c);
                if(c.ch != '(')
                    return -1; // falta liberar a pilha
                else
                    stack_pop(st);
            }
        }else{
            c.ch = s[i];
            stack_push(st, c);
        }  
    }
    result = stack_empty(st);
    stack_free(st);
    return result;
}

