sealed trait IntList
case object Nil extends IntList
case class Cons(v: Int, t: IntList) extends IntList

sealed trait BTree
case object Leaf extends BTree
case class IntNode(v: Int, left: BTree, right: BTree)
extends BTree

sealed trait Formula
case object True extends Formula
case object False extends Formula
case class Not(f: Formula) extends Formula
case class Andalso(left: Formula, right: Formula) extends Formula
case class Orelse(left: Formula, right: Formula)  extends Formula
case class Implies(left: Formula, right: Formula) extends Formula

object Hw1 extends App {

  println("Hw1!")

  def fibo(n: Int): Int ={
    _fibo(n+1)
  }
  def _fibo(n: Int): Int ={
    if(n<2) n
    else _fibo(n-1)+_fibo(n-2)
  }

  def sum(f: Int=>Int, n: Int): Int ={
    if (n==1) f(1)
    else f(n)+sum(f, n-1)
    
  }

  def foldRight(init: Int, ftn: (Int, Int)=>Int, list: IntList): Int = list match {
    case Cons(v,t) => ftn(foldRight(init, ftn, t), v)
    case Nil => init
  }


  def filter(f: Int => Boolean, list: IntList): IntList = list match{
    case Cons(v,t) => if (f(v)) Cons(v, filter(f,t)) else filter(f,t)
    case Nil => Nil
  }

  def iter[A](f: A => A, n: Int): A => A = {
    if (n>1) f compose iter(f,n-1)
    else f
  }

  
  def insert(t: BTree, a: Int): BTree = t match {
    case Leaf =>IntNode(a, Leaf, Leaf)
    case IntNode(v,left,right) if (v==a)=>IntNode(a,left,right)
    case IntNode(v,left,right) if (v<a)=>IntNode(v,left,insert(right,a))
    case IntNode(v,left,right) =>IntNode(v,insert(left,a),right)

  }
  def eval(f: Formula): Boolean = f match {
    case True => true
    case False=>false
    case Not(f)=>(!eval(f))
    case Andalso(left, right)=>eval(left)&&eval(right)
    case Orelse(left,right)=>eval(left)||eval(right)
    case Implies(left,right)=>(!eval(left))||eval(right)
  }
}