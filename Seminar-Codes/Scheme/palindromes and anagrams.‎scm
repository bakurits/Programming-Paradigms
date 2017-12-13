;;; This function reverses given sequence 
(define (reverse seq)
    (if (null? seq) '()
        (if (= (my-length seq) 1) seq
            (append (reverse (cdr seq)) (list (car seq)))
        )
    )
)

;;; This function evaluetes to 
;;; Length of sequence
(define (my-length seq)
    (if (null? seq) 0
        (+ 1 (my-length (cdr seq)))
    )
)

;;; This function checks if 
;;; given sequences are equal
(define (my-equal seq1 seq2)
    (if (not (= (my-length seq1) (my-length seq2))) #f
        (if (null? seq1) #t
            (and (= (car seq1) (car seq2)) (my-equal (cdr seq1) (cdr seq2)))
        )
    )
)

;;; This function checks if 
;;; Given sequence is palindrome
(define (is-pal seq)
    (if (my-equal (reverse seq) seq) #t
        #f
    )
)

;;; This function evaluates to 
;;; Number of ch's occurrences in str 
(define (count-in-str str ch)
    (if (null? str) 0
        (if (equal? ch (car str)) (+ 1 (count-in-str (cdr str) ch))
            (count-in-str (cdr str) ch)
        )
    )
)

;;; This function counts occurrences of
;;; Every lower-case english alphabet symbols
(define (char-seq str)
    (if (null? str) '(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
        (map (lambda (x) (count-in-str str x))
            '(a b c d e f g h i j k l m n o p q r s t u v w x y z)
        )
    )
)

;;; This function checks if
;;; Given strings are Anagrams
(define (is-anagram str1 str2)
    (equal? (char-seq str1) (char-seq str2))
)



