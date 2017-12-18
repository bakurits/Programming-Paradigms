/* Hello World N Times */
/* Print "Hello World" n amount of times. */
(define (nth n)
    (if (= n 0) '()
    (cons "Hello World\n" (nth (- n 1)))
    )
)

/* List Replication */
/* Given a list, repeat each element in the list, n amount of times */
(define (replOne x n)
    (if (= n 0) '()
        (cons x (replOne x (- n 1)))
    )
)

(define (repl n seq)
    (flatten (map (lambda(x) (replOne x n)) seq))
)

(define (flatten seq)
    (if (= (length seq) 0) '()
        (if (list? (car seq)) (append (flatten (car seq)) (flatten (cdr seq)))
            (cons (car seq) (flatten (cdr seq)))
        )
    )
)

/* Filter Array */
/* Filter a given array of integers and output only those values that are less than a specified value n */
(define (filter n seq)
    (if (= (length seq) 0) '()
        (if (< n (car seq)) (filter n (cdr seq))
            (cons (car seq) (filter n (cdr seq)))
        )
    )
)

/* Filter Positions in a List */
/* For a given list with n integers, return a new list removing the elements at odd positions */
(define (filterw n seq)
    (if (= (length seq) 0) '()
        (if (= (remainder (- n (length seq)) 2) 1) (filterw n (cdr seq))
            (cons (car seq) (filterw n (cdr seq)))
        )
    )
)

(define (filter seq)
    (filterw (length seq) seq)
)

/* Array Of N Elements */
/* Create an array of n integers */
(define (array n)
    (if (= n 0) '()
        (cons n (array (- n 1)))
    )
)

/* Reverse a List */
(define (reverse seq)
    (if (= (length seq) 0) '()
        (append (reverse (cdr seq)) (list(car seq)))
    )
)

/* Sum of Odd Elements */
(define (sum seq)
    (if (= (length seq) 0) 0
        (if (= (remainder (car seq) 2) 1) (+ (car seq) (sum (cdr seq)))
            (sum (cdr seq))
        )
    )
)

/* List Length */
(define (Length seq)
    (if (null? seq) 0
        (+ 1 (Length (cdr seq)))
    )
)

/* Update List */
/* Update the values of a list with their absolute values */
(define (abs seq)
    (if (= (length seq) 0) '()
        (if (< (car seq) 0) (cons (- 0 (car seq)) (abs (cdr seq)))
            (cons (car seq) (abs (cdr seq)))
        )
    )
)

/* Computing the GCD */
(define (Gcd n m)
    (if (= n 0) m
        (if (> n m) (Gcd m n)
            (Gcd (remainder m n) n)
        )
    )
)

/* Pascal's Triangle */
/* print the first n rows of Pascal's Triangle */
(define (nextLine seq)
    (cond ((= (length seq) 1) '(1))
          ((= (length seq) 2) (append (list (+ (car seq) 1)) (list 1)))
          (#t (cons (+ (car seq) (cadr seq)) (nextLine (cdr seq))))
    )
)

(define (pascalw n)
    (if (= n 0) '((1))
        (append (list(cons 1 (nextLine (car (pascalw (- n 1)))))) (pascalw (- n 1)))
    )
)

(define (reverse seq)
    (if (= (length seq) 0) '()
        (append (reverse (cdr seq)) (list(car seq)))
    )
)

(define (pascal n)
    (reverse (pascalw n))
)

/* Filter Elements */
/* Given a list you have to find those integers which are repeated at least K times.
   In case no such element exists you have to print -1. */
(define (count x seq)
    (if (null? seq) 0
        (if (= (car seq) x) (+ 1 (count x (cdr seq)))
            (count x (cdr seq))
        )
    )
)

(define (numbers) ('(0 1 2 3 4 5 6 7 8 9)))

(define (countAll seq)
    (map (lambda (x) (count x seq)) '(0 1 2 3 4 5 6 7 8 9))
)

(define (filterw seq k i)
    (if (null? seq) '()
        (if (< (car seq) k) (filterw (cdr seq) k (+ 1 i))
            (cons i (filterw (cdr seq) k (+ 1 i)))
        )
    )
)

(define (filter seq k)
    (let ((curr (filterw (countAll seq) k 0)))
        (if (null? curr) -1
            curr
        )
    )
)