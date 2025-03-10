(defun convert_tree (l)
  (cond
     ((null l) nil)
     ((= (cadr l) 0) (list (car l)))
     ((= (cadr l) 1) (cons (car l) 
                            (list  (convert_tree (cddr l)))))
     (T (cons (car l) 
              (list (convert_tree (cddr l)) 
              (convert_tree (skip_subtree (cddr l)))))) 

  )
)

(defun skip_subtree (l)
  (cond
     ((null l) nil)
     ((= (cadr l) 0) (cddr l))
     ((= (cadr l) 1) (skip_subtree (cddr l)))
     (T (skip_subtree (skip_subtree (cddr l))))
  )
)



(print (convert_tree '(A 2 B 1 F 0 C 2 D 0 E 0)))




   