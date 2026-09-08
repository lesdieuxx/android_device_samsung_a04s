#include <stddef.h>
/*
struct ASN1_item_small {
	char itype;	
	int utype;
	const void *templates;	
	long tcount;	
	const void *funcs;
	long size;
	const char *sname;	
}

;
struct ASN1_item_large {
	char itype;	
	long utype;	
	const void *templates;	
	long tcount;	
	const void *funcs;	
	long size;	
	const char *sname;	
};

struct ASN1_VALUE_st;
extern int ASN1_item_ex_new(struct ASN1_VALUE_st **pval, const void *it);
void *ASN1_item_new(const void *it)
{
	struct ASN1_VALUE_st *ret = NULL;

	// Change small (48 byte) into large (56 byte)
	struct ASN1_item_small *small = (struct ASN1_item_small *)it;
	struct ASN1_item_large large = {
		.itype = small->itype,
		.utype = small->utype,
		.templates = small->templates,
		.tcount = small->tcount,
		.funcs = small->funcs,
		.size = small->size,
		.sname = small->sname
	};

	if (ASN1_item_ex_new(&ret, &large) > 0) {
		return ret;
	}

	return NULL;
}*/

extern void *OPENSSL_sk_delete(void *sk, int i);
void *sk_delete(void *sk, int i) {
	return OPENSSL_sk_delete(sk, i);
}

extern void *OPENSSL_sk_dup(void *sk);
void *sk_dup(void *sk) {
	return OPENSSL_sk_dup(sk);
}
