;; inordine
(defun inordine(arb)
	(cond
    ((null arb) nil)
	(t (append
		(inordine (cadr arb)) 
		(list(car arb)) 
		(inordine (caddr arb))))
	)
)
	
(print( inordine '(a (b (c) (d)) (e (f) (g (h) (i)))) ))

(defun inord2(tree  c)
( cond
	((null tree) nil)
	((= (cadr tree) 0) 
		(cons (car tree)
			(cond
				((null c) (inord2 (cddr tree) c))
				(( = (cadr c) 1) (inord2 (cons (car c) (cons 0 (cddr tree))) (cddr c)))
				(t (cons(car c) (inord2 (cddr tree) (cddr c))))
			)
		)
	)

(T (inord2 (cddr tree) (cons (car tree) (cons (cadr tree) c))))))

(print (inord2 '(a 2 b 2 c 0 d 0  e 1 f 0 g 2 h 0 i 0) '()))


;; preordine
(defun preordine(arb)
	(cond
    ((null arb) nil)
	((null (cdr arb)) (list (car arb)))
		(t
			(append
        (list (car arb))
				(preordine (cadr arb))
				(preordine (caddr arb))
			)
		)
	)
)
(print(preordine '(a (b (c) (d)) (e (f) (g (h) (i))))))
;; postordine
(defun postordine(arb)
	(cond
    ((null arb) nil)
	((null (cdr arb))(list (car arb)))
		(t
			(append
				(postordine (cadr arb))
				(postordine (caddr arb))
        (list (car arb))
			)
		)
	)
)

(print(postordine '(a (b (c) (d)) (e (f) (g (h) (i))))))

;;nr of levels in a tree
(defun parcurg_st(tree nv nm)
	(cond
		((null tree) nil)
		((= nv (+ 1 nm)) nil)
		(T (cons (car tree) (cons (cadr tree) (parcurg_st (cddr tree) (+ 1 nv) 
		(+ (cadr tree) nm)))))
	)
)

(defun parcurg_dr(tree nv nm)
	(cond
		((null tree) nil)
		((= nv (+ 1 nm)) tree)
		(T (parcurg_dr (cddr tree) (+ 1 nv) (+ (cadr tree) nm)))
	)
)
(defun numberL (tree k)
	(cond 
	((null tree) k)
	(t (max
		(numberL(parcurg_st(cddr tree) 0 0) (+ k 1)) 
		(numberL(parcurg_dr(cddr tree) 0 0) (+ k 1))))
		
	)
)
;(print(numberL '(A 2 B 1 C 0 D 0 E 2 F 0 G 2 H 0 I 0) 0))
	
(defun find_left (tree nodes edges)
  (cond
   	((null tree) nil)
    ((= nodes (+ 1 edges)) nil)
    (t (cons (car tree) 
             (cons (cadr tree) 
                   (find_left (cddr tree) (+ 1 nodes) (+ (cadr tree) edges))
             )
       )
    )
  )
)
(defun find_right (tree nodes edges)
  (cond
   	((null tree) nil)
    ((= nodes (+ 1 edges)) tree)
    (t (find_right (cddr tree) (+ 1 nodes) (+ (cadr tree) edges)))
  )
)

(defun find_level(tree target k)
	(cond
	((null tree) nil)
	((equal (car tree) target) k)
	(t (or
		(find_level (find_left (cddr tree)  0 0) target (+ k 1))
		(find_level (find_right (cddr tree)  0 0) target (+ k 1))
		))))

;(print(find_level '(A 2 B 2 C 0 D 0 E 2 F 0 G 2 H 0 I 0) 'H 0))	


(defun left(l)
  (find_left (cddr l) 0 0)
)


(defun right(l)
  (find_right (cddr l) 0 0)
)

(defun checkExistence(l elem)
  (cond
    ((null l) nil)
    ((equal (car l) elem) t)
    (t (checkExistence (cdr l) elem))
  )
)

(defun checkExistenceLeft(l elem)
  (checkExistence  (left l) elem)
)

(defun checkExistenceRight(l elem)
  (checkExistence  (right l) elem)
)

(defun find_path(l elem)
  (cond
    ((null l) nil)
    ((equal (car l) elem) (list elem))
    ((checkExistenceRight l elem) (cons (car l) (find_path (right l) elem)))
    ((checkExistenceLeft l elem) (cons (car l) (find_path (left l) elem)))
  )
)

;(print(find_path '(A 2 B 2 C 0 D 0 E 2 F 0 G 2 H 0 I 0) 'G ))


(defun nodes(l counter level)
  (cond
    ((null l) nil)
    ((equal counter level) (list (car l)))
    (t (myappend (nodes (left l) (+ 1 counter) level) (nodes (right l) (+ 1 counter) level)))
  )
)

;(print(nodes '(A 2 B 2 C 0 D 0 E 2 F 0 G 2 H 0 I 0) 0 2))

(defun convert_tree2to1(l)
    (cond
         ((null l) nil)
         ((and (not (null (cadr l))) (not (null (caddr l)))) (append (list (car l)) '(2) (convert_tree2to1(cadr l))
                                                                     (convert_tree2to1(caddr l))))
         ((not (null (cadr l))) (append (list (car l)) '(1) (convert_tree2to1(cadr l)) ))
         ((not (null (caddr l))) (append (list (car l)) '(1) (convert_tree2to1(caddr l)) ))
         (T (append (list (car l)) '(0)))
    )
)

;(print(convert_tree2to1 '(A(B (C)(D)) (E (F (J)) (G(H)(I))))))




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

;(print (convert_tree '(A 2 B 1 F 0 C 2 D 0 E 0)))

(defun parse_left2 (tree)
  (cond
    ((null tree) nil)
    ((null (cdr tree)) nil)
    (t( cadr tree)))) 

(defun parse_right2 (tree)
  (cond
    ((null tree) nil)
    ((null (cddr tree)) nil)
    (t (cddr tree)))) 
	
;(print(parse_left2 '(a (b (c) (d)) (e (f) (g (h) (i))))))

(defun find-level2 (tree target level)
  (cond
    ((null tree) 0)
    ((equal (car tree) target) level)
	( (atom (car tree)) (find-level2 (cdr tree) target level) )
    ((listp (car tree)) 
		(+(find-level2 (car tree) target (+ 1 level)) 
			(find-level2 (cdr tree) target level)))
	
	))

(print(find-level2 '(a (b (c) (d)) (e (f) (g (h) (i)))) 'e 0))


(defun find_path2(tree elem)
  (cond
    ((null tree) nil)
    ((equal (car tree) elem) (list elem))
	( (atom (car tree)) (find_path2 (cons (car tree)( cdr tree)) elem))
	((listp (car tree) (find_path2 (car tree) elem) (find_path2 (cdr tree) elem)))
	 
  )
)

;(print(find_path2 '(a (b (c) (d)) (e (f) (g (h) (i)))) 'e ))

(defun replace_with_level(tree level)
	(cond
	((null tree) nil)
	( (atom (car tree)) (append (list (find-level2 tree (car tree) level) )(replace_with_level (cdr tree) level)))
	((listp (car tree)) (append (replace_with_level  (car tree) (+ 1 level)) (replace_with_level (cdr tree) level)))
	))


;(print(replace_with_level '(a (b (c) (d)) (e (f) (g (h) (i)))) 0))			
(defun find_max_occurences(l maxApp level)
	(cond 
	((null l) level)
	( (> (nrOcc l (car l)) maxApp) (find_max_occurences (cdr l) (nrOcc l (car l)) (car l) ))
	(t (find_max_occurences(cdr l) maxApp level))
))
; (print (find_max_occurences '(0 1  3 1 2 2 3 3)  0 0))
  

(defun maxnodeslevel(tree level)
	(cond 
	( (null tree) nil)
	( (and (atom (car tree))(= (find-level2 tree (car tree) 0) 
		(find_max_occurences (replace_with_level tree 0) 0 0)))
			(cons (car tree) (maxnodeslevel (cdr tree)  level)))
	( (listp (car tree)) (cons (maxnodeslevel (car tree) (+ 1 level)) (maxnodeslevel (cdr tree) level)))
	(t (maxnodeslevel (cdr tree) level))
	)
)
;(print (maxnodeslevel '(a (b (c) (d (m))) (e (f) (g (h) (i)))) 0) )

(defun my_max (a b)
    (cond
	((> a b) a)
	(t b)
	)
)

(defun nr_niveluri(l)
    (cond
        ((null l) 0)
        ((null (cdr l)) 1)
        (t (+ 1 (my_max (nr_niveluri (cadr l)) (nr_niveluri (caddr l)))))
    )
)
(print (nr_niveluri '(a (b (c) (d)) (e (f) (g (h) (i))))))

(defun echilibrat(l)
    (cond
        ((null l) t)
        (t (AND (< (abs (- (nr_niveluri (cadr l)) (nr_niveluri (caddr l)))) 2) (echilibrat (cadr l)) (echilibrat (caddr l))) )
    )
)

(print (echilibrat '(a (b (c) (d)) (e  (g (h) (i))))))
;; drumul de la radacina la un anumit nod
(defun verificare(l e)
  (cond
    ((and (atom l) (eq l e)) (list t))
    ((listp l) (mapcan #'(lambda (x) (verificare x e))l))
  )
)


(defun functieMain(l e)
  (cond
    ((atom l) nil)
    ((car (verificare l e)) (append (list (car l)) (mapcan #'(lambda (x) (functieMain x e))l)))
  )
)