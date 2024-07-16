/*
 * structures.h
 *
 *  Created on: 2024年5月16日
 *      Author: 宋元
 */

#ifndef USER_STRUCTURES_H_
#define USER_STRUCTURES_H_
#define MAX_PRODUCTS 100
#define MAX_STRING_LENGTH 100
#define MAX_PRODUCTS 100 //规定最多可以储存100个商品信息

typedef struct ProductInfo {
    char productID[MAX_STRING_LENGTH+1];
    u8 productPrice;
    char productName[MAX_STRING_LENGTH+1];
    u8 productWeight;
    char productPriceStr[MAX_STRING_LENGTH];
    char productWeightStr[MAX_STRING_LENGTH];
    u8 productNum;
    struct ProductInfo *next;
    struct ProductInfo *current;
} ProductInfo,*Pro;

extern ProductInfo product;
//extern struct ProductInfo product;

typedef struct{
    uint8_t size;
    ProductInfo *head;
} ProductInfoList;

extern ProductInfoList list;





#endif /* USER_STRUCTURES_H_ */
