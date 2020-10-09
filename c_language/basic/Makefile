scalar: scalar_product.out
	./scalar_product.out
is_prime: is_prime.out
	./is_prime.out
is_prime.out:
	gcc is_prime.c -o is_prime.out
scalar_product.out:
	gcc scalar_product.c -o scalar_product.out
clean:
	find . -type f -name '*.out' -delete
