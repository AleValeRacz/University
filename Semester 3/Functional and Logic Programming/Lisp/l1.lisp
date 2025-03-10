(defun dot_product (l1 l2)
  (cond
  ( (null l1) 0)
  (t (+ (* (car l1) (car l2)) 
         (dot_product (cdr l1) (cdr l2)))))) 


(defun my_max (a b)
    (if (> a b) a b)
)


(print(dot_product '(1 5 3) '(4 2 7)))
(print(dot_product '() '()))


(defun list_depth(l d)
    (cond
    ((null l) (+ d 1))
    ((listp (car l)) (Max (list_depth (car l) (+ d 1)) (list_depth (cdr l) d)))
    (t (list_depth (cdr l) d)))
)


(print (list_depth '(6 5 1) 0))
(print (list_depth '(6 (2 3 (4) (5) (6 (7)))) 0))


(defun insert_in_list(l e)
(cond
      ((null l) (list e))
      ((= (car l) e) l)
      ((< (car l) e) (cons (car l) (insert_in_list(cdr l) e)))
      (T (cons e l))
)
)


(defun sort_list (l)
(cond
    ((null l) nil)
    (T (insert_in_list (sort_list(cdr l)) (car l)))
)

)


(print (sort_list '(3 1 5 4 2 1 3 9 2 1 4)))


(defun my_search(l e)
  (cond
      ((null l) nil)
      ((= e (car l)) T)
      (T (my_search (cdr l) e))
  )
)

(defun intersect (l1 l2)
(cond
    ((null l1) nil)
    ((my_search  l2 (car l1)) (cons (car l1) (intersect (cdr l1) l2)))
    (T (intersect (cdr l1) l2))
)
)

(print (intersect '(1  4 5 2) '(3 2 6 5)))
 
