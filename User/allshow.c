/*
 * allshow.c
 *
 *  Created on: 2024年5月16日
 *      Author: 宋元
 */
#include "L610.h"
#include "stdlib.h"
#include <string.h>
#include "allshow.h"

// 初始化链表
void initProductList(ProductInfoList *list)
{
    list->head = NULL;
    list->size = 0;
}

// 在链表尾部插入商品信息
void insertProduct(ProductInfoList *list, ProductInfo product)
{
    ProductInfo *newProduct = (ProductInfo *)malloc(sizeof(ProductInfo));
    if (newProduct == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    *newProduct = product;
    newProduct->next = NULL;

    if (list->head == NULL) {
        list->head = newProduct;
    } else {
        ProductInfo *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newProduct;
    }
    list->size++;
}

// 销毁链表
void destroyProductList(ProductInfoList  *list)
{
    ProductInfo *current = list->head;
    while (current != NULL) {
        ProductInfo *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
}

// 打印链表中的商品信息
void printProductList(ProductInfoList *list)
{
    ProductInfo *current = list->head;
    while (current != NULL) {
        printf("Product ID: %s\n", current->productID);
        printf("Product Name: %s\n", current->productName);
        printf("Product Price: %.2f\n", current->productPrice);
        printf("Product Weight: %.2f\n", current->productWeight);
        printf("-----------------\n");
        current = current->next;
    }
}
void deleteProduct(ProductInfoList *list, const char *productID)
{
    if (list->head == NULL) {
        // 链表为空
        return;
    }

    ProductInfo *current = list->head;
    ProductInfo *previous = NULL;

    // 查找要删除的节点
    while (current != NULL && strcmp(current->productID, productID) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        // 没有找到要删除的节点
        printf("Product with ID %s not found.\n", productID);
        return;
    }

    // 删除节点
    if (previous == NULL) {
        // 要删除的节点是头节点
        list->head = current->next;
    } else {
        // 要删除的节点在链表中间或尾部
        previous->next = current->next;
    }

    free(current);
    list->size--;
    printf("Product with ID %s deleted.\n", productID);
}
int ALLshow()
{
        ProductInfoList  productList;
        initProductList(&productList);

        // 循环接收商品信息并插入链表
        for (int i = 0; i < MAX_PRODUCTS; i++) {
            ProductInfo product = L610_Recive();
            if (strlen(product.productID) == 0) {
                // 如果收到的商品信息的ID为空，则结束接收
                break;
            }
            insertProduct(&productList, product);
        }

        // 打印链表中的商品信息
        printf("Product List:\n");
        printProductList(&productList);

//        // 销毁链表
//        destroyProductList(&productList);

        return 0;


}

//Pro createList()
//{
//
//     int n=5;
//     Pro list =NULL;
//     for(int i=0;i<=n;i++)
//     {
//         ProductInfo productPriceStr=L610_Recive();
//         Pro p_new = (Pro)malloc(sizeof(ProductInfo));
//         if (p_new == NULL)
//         {
//            fprintf(stderr, "Memory allocation failed\n");
//            exit(1);
//         }
//         p_new->productPriceStr =productPriceStr;
//         p_new ->next =list;
//         list = p_new ;
//
//     }
//     return list;
//}
//void printList(Pro list)
//{
//    while(list!=NULL)
//    {
//      printf("%f",list->productPriceStr);
//      list = list ->next;
//
//    }
//}
//void freeProductList(Pro list)
//{
//    while (list != NULL)
//    {
//        Pro temp = list;
//        list = list->next;
//        free(temp);
//    }
//}
//
////测试
//
//void test()
//{
//
//    Pro list =createList();
//    printList(list);
//    freeProductList(list);
//
//}

//此函数用于将目前添加的商品的信息给到屏幕上

