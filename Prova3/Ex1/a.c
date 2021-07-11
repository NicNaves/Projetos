int list_erase_even(TDLinkedList *li){
  if(li == NULL)
    return -1;
  if(li->begin == NULL)
     return -1;
  DLNode *aux = li->begin;
  int aux = size; // quem é size?
  int ret;
  for(int pos = 0; pos < aux; pos++ ){
    if (aux->next == NULL)
        return 0;
    if (aux->data % 2 == 2)
      if((ret = list_erase(TDLinkedList *li, int i)) != 0) // chamada de função errada
        return -1;
        // nada faz o ponteiro andar
  }
  return 0;
}