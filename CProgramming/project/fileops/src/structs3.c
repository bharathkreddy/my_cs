#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product{
    char *itemName;
    int quantity;
    float price;
    float amount;
};

void readinfo(struct product *prod){
    char temp[100];
    printf("Name: ");
    scanf("%99s", temp);
    prod->itemName = malloc(strlen(temp)+1);
    strcpy(prod->itemName, temp);
    printf("Quantity: ");
    scanf("%d", &prod->quantity);
    printf("Price: ");
    scanf("%f", &prod->price);
    prod->amount = prod->price * prod->quantity;
}

void printinfo(struct product *prod){
    printf("Name: %s\nQuantity: %d\nPrice: %f\nAmount: $%f\n\n", prod->itemName, prod->quantity, prod->price, prod->amount);
}

int main(){
    
    struct product *p = malloc(sizeof(*p));
    readinfo(p);
    printinfo(p);
    printf("P lives at :%p\n", &p);
    free(p->itemName);
    free(p);


}
