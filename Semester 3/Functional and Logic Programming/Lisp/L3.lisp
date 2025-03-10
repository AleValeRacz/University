
(defun replaceEwithL1(l e l1)
    (cond
		((null l) nil)
        ((and (atom l) (= l e)) l1)
        ((atom l) (list l))
        (t (list (apply #'append  (mapcar #'(lambda (lst) (replaceEwithL1 lst e l1)) l))))
		;(t (list (mapcan #'(lambda (lst) (replaceEwithL1 lst e l1)) l)))

    )
)  

(defun main (l e l1)
	(car (replaceEwithL1 l e l1))
)


(print (main '(2 5 4 1 5  3 4 2) 4 '(7 7)))	
(print (main '(2 (5 4 (1) 5 ) 3 4 2) 4 '(7 7)))	


