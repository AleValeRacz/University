
(defun f(L)
	(cond
		((atom L) -1)
		(( >(F (car L)) 0) (+ (car L) (F (car L)) (F (cdr L))))
		(T (F(cdr l)))
	)
)

;(print(f '((2 3 2) 1 4)))

(defun f2(L)
	((lambda (v)
	(cond
		((atom L) -1)
		((> v 0) (+ (car l) v (F2 (cdr l))))
		(T (F2(cdr l)))
	)
	)
	(f (car L))
))


(defun f3(G l)
	(cond
	((null l) nil)
	(> (funcall G l) 0) (cons (funcall G l) (f3 (cdr l)))
	(t (funcall G l)
	)
)
)

(defun f4 (G l)
	((lambda (v)
		(cond
			((null l) nil)
			((> v 0) (cons v (f4 (cdr l))))
			(t v)
		)
	)
	( funcall g l)
	)
)


		
	
		
	
;(print(f2 '((2 3 2) 1 4)))


(defun incrementNrs(l)
	(cond
		( (and (numberp l) (evenp l)) (+ 1 l))
		( (atom l) l)
		(t (mapcar #'(lambda (x) (incrementNrs x)) l))
	)
)

;(print (incrementNrs '(1 s 4 (2 f (7)))))


(defun ReplaceAtKLvl(l lvl e)
	(cond
		((and (atom l) (evenp lvl)) e)
		( (atom l) l)
		(t (mapcar #'(lambda (x) (ReplaceAtKLvl x (+ 1 lvl) e)) l))
	)
)

;(print (ReplaceAtKLvl '(a (b (g)) (c (d(e)) (f))) 0 'H))

(defun G(F l)
	(FUNCALL F L)
	) 
	
	
(defun multiplyWithLvl(l lvl)
	(cond
	((numberp l) (* l lvl))
	((atom l) l)
	(t (mapcar #'(lambda(x) (multiplyWithLvl x (+ 1 lvl))) l))
	)
)

(print (multiplyWithLvl '(1(2(A (B))) (3(4(C(5))))) 0) )


(defun G(l) (list (car l) (car l)))

(setq Q 'G) 
(setq P 'Q)

;(print(funcall (eval P) '(A B C)))


(defun F(L)
	((lambda(x)
		(cond
			((null l) nil)
			( (listp (car l)) (append x (f (cdr l)) (car (f x))))
			(t (list (car l)))
		)
	)
	( F(car l))
	)
)

(defun f (X &optional y)
	(cond
		((null y) (cdr x))
		(t (cons (car x) y))
	)
)

; (2 3 (5 6))
(print(append (f'(1 2)) (f '(3 4) '(5 6))))


(defun replaceEWithE1(l e e1 lvl)
	(cond
		((null l) nil)
		((and (atom l) (eq l e) (oddp lvl)) e1)
		( (atom l) l)
		(t (mapcar #'(lambda (x) (replaceEWithE1 x e e1 (+ 1 lvl))) l))
	)
)

(print (replaceEWithE1 '() 'd 'f 0))


(defun removeMul3(l)
	(cond 
	( (and (numberp l) (=(mod l 3) 0)) nil)
	( (atom l)  l)
	(t (mapcar #'(lambda (x) (removeMul3 x)) l))
	)
)

;(print(removeMul3 '(1 (2 A (3 A)) (6))))



(defun atKlvl(l lvl k)
	(cond
		((and (atom l) (= lvl k)) (list l))
		( (atom l) nil)
		(t (mapcan #'(lambda (x) (atKlvl x (+ 1 lvl) k)) l))
	)
)

;(print (atKlvl '(a (b (g)) (c (d(e)) (f))) -1 2))




(defun atEvenlvl(l lvl e)
	(cond
		((and (evenp lvl) (eq e l)) 1)
		( (atom l) 0)
		(t (apply #'max(mapcar #'(lambda (x) (atEvenlvl x (+ 1 lvl) e)) l)))

	)
)

(defun mainEvenLvl(l e)
	(cond
	((= (atEvenlvl l -1 e) 1) t)
	(t nil)
	)
)
	
;(print (mainEvenLvl'(a (b (g)) (c (d(e(h))) (f)))  'c))


;; drumul de la radacina la un anumit nod
(defun verificare(l e)
  (cond
    ((and (atom l) (eq l e)) (list t))
    ((listp l) (mapcan #'(lambda (x) (verificare x e))l))
  )
)

(defun myappend (l1 l2)
	(cond
	((null l1) l2) 
	(t (cons (car l1) (myappend (cdr l1) l2)))
	
))
	 

(defun DrumMain(l e)
  (cond
    ((atom l) nil)
    ((car (verificare l e)) (myappend (list (car l)) (mapcan #'(lambda (x) (DrumMain x e))l)))
  )
)

;(print(DrumMain '(a (b(g)) (c(d(e))(f))) 'e))


(defun SizeOfTree(l lvl)
	 (cond
	 ((null l) lvl)
	 ((atom l) lvl)
    (t (apply #'max(mapcar #'(lambda (x) (SizeOfTree x  (+ 1 lvl)))l)))
))


(defun nivelNod(l e nivel)
  (cond
    ((and (atom l) (eq l e)) nivel)
    ((atom l) -1)
    (t (apply #'max(mapcar #'(lambda (x) (nivelNod x e (+ 1 nivel)))l)))
  )
)
(defun nrLevels(x)
  (cond
    ((null x) 0)
    (t (+ (apply #'max (cons 0 (mapcar #'nrLevels (cdr x)))) 1))
  )
)

(defun depth(x e curr)
  (cond
    ((equal (car x) e) curr)
    (t (apply #'min (cons 100000 (mapcar #'(lambda (a) (depth a e (+ 1 curr))) (cdr x)))))
  )
)
  
(defun calc (x e)
  (- (nrLevels x) (nivelNod x e 0))
)


;(print (calc '(a (b (g)) (c (d (e)) (f))) 'b))







;(print (mainNivel '(a (b (g)) (c (d (e)) (f))) 'a))

	
 
(defun g(f l)
	(funcall f l)
)
(print (g #'(lambda(L)(g #'cdr l))  '(1 2 3)))


(defun g(l) (mapcon #'list l))
(print (g '( 1 2 3)))
(print (mapcon #'g '(1 2 3)))

		


(defun g(l) (list (car l) (car l)))
(setq q 'g)
(setq p 'q)
(print (funcall (eval p) '(A B C)))





