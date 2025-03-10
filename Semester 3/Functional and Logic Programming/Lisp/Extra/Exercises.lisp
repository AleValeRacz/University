;6 a) 
(defun dubleElemOnPoz(l current poz)
	(cond
	((null l) nil)
	( (= poz  current) (cons (car l) (cons (car l) (cdr l))))
	(T  (cons (car l) (dubleElemOnPoz (cdr l ) (+ 1 current) poz)))
	
	)
)

;(print ( dubleElemOnPoz'(3 4 2 1 5) 1 3)) 

;6 b)
(defun Pairs( a b)

	(cond
	((null a) nil)
	(t (cons (list (car a ) (car b)) (Pairs(cdr a) (cdr b))))
	
	)
)

;(print (Pairs '(A B C) '(1 2 3)))

;6 d) nr atomilor de la nivelul superficial

(defun NrAtomsSurface (l)

(cond
	((null l) 0)
	( (atom (car l)) ( + 1 (NrAtomsSurface( cdr l))))
	(t (NrAtomsSurface(cdr l)))
)
)
;(print (NrAtomsSurface '(3 2 (A 3) C 1 (A (C)) F ))) 


;7 c) 

(defun lastElem(l)
	(cond
		((and (null (cadr l)) (listp (car l))) (lastElem(car l)))
		( (null (cadr l)) (car l))
		( t (lastElem (cdr l)))
	)
)
(defun replceSublistLastE(l)
	(cond
		((null l) nil)
		( (listp (car l)) (cons (lastElem (car l))  (replceSublistLastE (cdr l) )))
		( t (cons (car l) (replceSublistLastE (cdr l))))
	)
)

;(print (lastElem '( 6 4 1 (5 3 ))))
;(print (replceSublistLastE '(a (b c) (d (e (f))))))

; 8 c)

(defun exista( l e)
( cond
	((null l) nil)
	( (eq (car l) e) T)
	(t (exista (cdr l) e))
)
)

;not liniar too
(defun nrOcc( l e)
	(cond
		((null l) 0)
		( (listp (car l)) (+ (nrOcc (car l) e) (nrOcc (cdr l) e)))
		( (= (car l) e) (+ 1 (nrOcc (cdr l ) e)))
		(t (nrOcc (cdr l ) e)) 
	)
)

;(print(exista '(4 5 3) 3))
;(print(nrOcc '(6 4 (6 5)  6 1) 6))

(defun listaAtomilor(l new)
	(cond
		((null l) new)
		( (listp (car l)) (listaAtomilor (cdr l) (listaAtomilor(car l) new)))
		(  (not (exista new (car l))) (listaAtomilor(cdr l) (cons  (car l) new)))
		(t (listaAtomilor (cdr l) new))
	)
)

;(print (listaAtomilor '(1 (2 (1 3 (2 4) 3) 1) (1 4)) '()))

;; lista atomilor non numerici in ordine inversa

(defun atomiNonNumerici (l)
(cond
	(( null l) nil)
	( ( and (atom (car l)) (not (numberp (car l)))) (append (list(car l)) (atomiNonNumerici(cdr l))))
	( (atom (car l)) (atomiNonNumerici(cdr l)))
	( t (append (atomiNonNumerici(car l)) (atomiNonNumerici (cdr l))))
	
)
)

;(print(atomiNonNumerici '(((A 3 B) C 1) 3 F (D E) 7 G)))

(defun inverseaza(l acc)
	(cond
		((null l) acc)
		(t (inverseaza (cdr l) (cons (car l) acc)))
	)
)


;(print (inverseaza(atomiNonNumerici '(((A 3 B) C 1) 3 F (D E) 7 G)) '()))
	

(defun deletePosx2(l next current)
	(cond
		((null l) nil)
		( (= next current) (deletePosx2 (cdr l) (* 2 next) (+ 1 current)))
		( t (cons (car l) (deletePosx2 (cdr l) next (+ 1 current))))
	)
)

;(print (deletePosx2 '(1 2 3 4 5 6) 1 1))



(defun insert-at (x l pos)
	( cond
	((= pos 0) (cons x l))
	( t (cons (car l) (insert-at x (cdr l) ( - pos 1))))
	)
)

(defun lungime(l)
    (cond
        ((null l) 0)
        (t (+ 1 (lungime (cdr l))))
    )
)

;(print (lungime '(1 2 3 4 5 6)))

;(print (insert-at 4 '(1 2 3 5) 4))

(defun inserare (atom l pos)
	(cond 
		((<= pos (lungime l)) (cons  (insert-at atom l pos) (inserare atom l (+ 1 pos))))
)
)
;(defun inserare (x l)
; (mapcar #'(lambda (pos) (insert-at x l pos)) l))
			 

;(print (inserare '1 '(2 3) 0))

(defun eVale (l flag)
	(cond
		((and (null l) (= 1 flag)) T)
		((and (null l) (= 0 flag)) nil)
		((and (null (cadr l)) (= 1 flag)) T)
		((and (null (cadr l)) (= 0 flag)) nil)
		((and (> (car l) (cadr l)) ( = 0 flag)) (eVale (cdr l) 0))
		(( <(car l) (cadr l)) (eVale (cdr l) 1))
		(T nil)
	)
)

(defun valeMain(l)
	(cond 
		((and ( >= (lungime l) 3) (> (car l) (cadr l))) (eVale l 0))
		(T nil)
	)
)

;(print (valeMain '( 10 8 6 17 18 29)))

(defun isLiniar (l)
	(cond 
		((null l) t)
		((atom (car l)) (isLiniar (cdr l)))
		(T nil)

))
;(print (isLiniar '(5 6 7 1)))
;(print (isLiniar '(5 (6 7) 1)))
(defun is-even (n)
  (= (mod n 2) 0))



(defun deleteSublistsEvenNrElem (l)
	(cond 
		((null l) nil)
		((and 
			(listp (car l)) 
			(isLiniar (car l)) 
			(= (mod (lungime (car l)) 2) 0)) 
				(deleteSublistsEvenNrElem (cdr l)))
				
		( (listp (car l))
			(cons (deleteSublistsEvenNrElem (car l)) (deleteSublistsEvenNrElem (cdr l))))
		( t (cons (car l) (deleteSublistsEvenNrElem (cdr l))))
	)
)

;(print (deleteSublistsEvenNrElem '((2 3 4) (6 (7 8) ((7 9) 8)) (6 8) 9))) 
			
		

(defun reverseSequences (l acc)
	(cond 
	((null l) acc)
	((atom (car l)) (reverseSequences (cdr l) (cons (car l) acc)))
	((listp (car l)) (append acc (list(reverseSequences ( car l) '())) (reverseSequences (cdr l) '()) ))      
	))
	
;(print (reverseSequences '(a b c (d (e f) g h i)) '()))

(defun pairs(l atom)
	(cond 
	((null l) nil)
	( (numberp (car l)) (pairs (cdr l) atom)) 
	 (t (cons (list atom (car l)) (pairs (cdr l) atom)))
	))
	
(defun allPairs (l)
	(cond
	((null l) nil)
	( (numberp (car l)) (allPairs (cdr l)))
	( t (append (pairs (cdr l) (car l)) (allPairs (cdr l))))
	))

;(print (allPairs '( a 1 b 3 c d)))
 
 (defun myappend (l1 l2)
	(cond
		((null l1) l2)
		(t (cons (car l1) (myappend (cdr l1) l2)))
	)
)

(defun myremove (e l)
  (cond
    ((atom l) l)
    ((eql (car l) e) (myremove e (cdr l)))
    (t (cons (car l) (myremove e (cdr l))))
  )
)

(defun list_depth(l d)
    (cond
    ((null l) (+ d 1))
    ((listp (car l)) (Max (list_depth (car l) (+ d 1)) (list_depth (cdr l) d)))
    (t (list_depth (cdr l) d)))
)


;(print (list_depth '(6 5 1) 0))
;(print (list_depth '(6 (2 3 (4) (5) (6 (7)))) 0))


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


;(print (sort_list '(3 1 5 4 2 1 3 9 2 1 4)))


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

;(print (intersect '(1  4 5 2) '(3 2 6 5)))

;; 2 c)
(defun allListsList (l)
	(cond
	((null l) nil)
	((listp (car l)) (cons (car l)  (append (allListsList( car l)) (allListsList (cdr l)))))
	( t (allListsList (cdr l)))
))
(print (allListsList '(1 2 (3 (4 5) (6 7)) 8 (9 10)) ))
	
 ;;nr tuturor listelor
 (defun nrSubliste (l)
	(cond 
	((null l) 0)
	( (listp (car l)) (+ (+ 1 (nrSubliste (car l))) (nrSubliste (cdr l))))
	(t (nrSubliste (cdr l)))
))
(print (nrSubliste '(1 2 (3 (4 5) (6 7)) (8 (9 10))) ))

(defun cmmdc(a b div)
    (cond
        ((= div 1) 1)
        ((AND (= (mod a div) 0) (= (mod b div) 0)) div)
        (t (cmmdc a b (- div 1)))
    )
)

(defun cmmdcMain(a b)
    (cond
        ((OR (= a 1) (= b 1)) 1)
        ((= a b) a)
        ((> a b) (cmmdc a b b))
        ((< a b) (cmmdc a b a))
    )
)

(defun cmmdcLista(l)
    (cond
        ((null l) 1)
        ((listp (car l)) (cmmdcMain (cmmdcLista (car l)) (cmmdcLista (cdr l))))
        ((numberp (car l)) (cmmdcMain (car l) (cmmdcLista (cdr l))))
        (T (cmmdcLista (cdr l)))
    )
)

(defun inverseaza(l)
	(cond
		((null l) nil)
		(t (append (inverseaza (cdr l)) (list (car l))))
	)
)
(defun succesor (l carry)
	(cond 
	((and (null l) (> carry 0)) carry)
	((null l) nil)
	( (and (= (car l) 9) (= carry 1)) (cons 0 (succesor (cdr l) 1)))
	( t (cons (+ (car l) carry) (succesor (cdr l) 0)))
	)
)

(defun succesorMain(l)
	(inverseaza (succesor(inverseaza l) 1)))

(print( succesorMain '(1799)))


(defun cmmmc(A B Factor)
    (cond
        ((AND (>= A B) (= (mod A B) 0)) A)
        ((AND (>= B A) (= (mod B A) 0)) B)
        (T (cmmmc (+ A Factor) B Factor))
    )
)

(defun cmmmcMain(a b)
    (cond
        ((>= A B) (cmmmc B A B))
        ((>= B A) (cmmmc A B A))
    )
)

(defun cmmmcLista(l)
    (cond
        ((null l) 1)
        ((listp (car l)) (cmmmcMain (cmmmcLista (car l)) (cmmmcLista (cdr l))))
        ((numberp (car l)) (cmmmcMain (car l) (cmmmcLista (cdr l))))
        (T (cmmmcLista (cdr l)))
    )
)


 
(Defun Fc(x) #'(lambda (y) (mapcar y(cddr x))))
(print (funcall (fc (quote ((1) (2) (3) (4)))) #'car))


(defun g(l) (list (car l) (caddr l)))
(setq q 'g)
(setq p 'q)
(print(apply (eval p) (list '(a b c))))