
(defun cmmmc(a b c)
    (cond
        ( (= (mod a b) 0) a)
        ((= (mod b a) 0) b)
        (t (cmmmc (+ a c) b c))
    )
)

(defun cmmmcMain(a b)
    (cond
        ((>= a b) (cmmmc b a b))
        (t (cmmmc a b a))
    )
)



(defun cmmmcList(l)
    (cond
        ((null l) 1)
        ((listp (car l)) (cmmmcMain (cmmmcList (car l)) (cmmmcList(cdr l))))
        ((numberp (car l)) (cmmmcMain (car l) (cmmmcList (cdr l))))
        (t (cmmmcList (cdr l)))
    )
)

(print (cmmmcList '(12 2 4 6 8)))
(print (cmmmcList '(8 ((2) 7 6))))
(print (cmmmcList '(a b c d 2 2)))
