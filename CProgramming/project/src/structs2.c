#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct product{
    char *itemName;
    int quantity;
    float price;
    float amount;
};

void readProduct(struct product *p){
    char temp[100];
    printf("Name: ");
    scanf("%s", temp);
    p->itemName = malloc(strlen(temp)+1);
    strcpy(p->itemName, temp);
    printf("quantity: ");
    scanf("%d", &p->quantity);
    printf("Price: ");
    scanf("%f", &p->price);
    p->amount = p->quantity * p->price;
}

int main(){

    
    struct product *p = malloc(sizeof(struct product));
    if(!p){
        printf("Heap allocation failed.\n");
        return 0;
    }

    readProduct(p);
    printf("Name: %s\nQuantity: %d\nPrice: %f\nAmount:%f\n\n", p->itemName, p->quantity, p->price, p->amount);

    free(p->itemName);
    free(p);

}
