;;; This function removes all occurrences
;;; Of elem from seq and evaluates to this new list.
(define (remove seq elem)
    (if (null? seq) '()
        (if (equal? (car seq) elem) (remove (cdr seq) elem)
            (cons (car seq) (remove (cdr seq) elem))
        )
    )
)


;;; This function checks if given list
;;; Is wavy (up-down) 
(define (is-up-down seq sign)
    (if (< (length seq) 2) #t
        (if (equal? sign <) 
            (and (< (car seq) (cadr seq)) (is-up-down (cdr seq) >))
            (and (> (car seq) (cadr seq)) (is-up-down (cdr seq) <))
        )
    )
)


;;; This function generates all possible
;;; Permutations and evaluates to this list of permutations
(define (all-permutation seq)
    (if (null? seq) '(())
        (apply append (map (lambda (elem)
                                (map (lambda (curPerm)
                                        (cons elem curPerm)
                                    )
                                (all-permutation (remove seq elem))
                                )
                            )
                            seq
                        )
        )
    )
)


;;; This function finds all wavy
;;; (up-down) permutations and evaluates to
;;; List of them
(define (only-up-down seq)
    (if (null? seq) seq
        (if (is-up-down (car seq) <)
            (cons (car seq) (only-up-down (cdr seq)))
            (only-up-down (cdr seq))
        )
    )
)



;;; This function is simple wrapper
;;; On "only-up-down"
(define (up-down-permutations seq)
    (only-up-down (all-permutation seq))
)

