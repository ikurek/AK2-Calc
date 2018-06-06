import java.math.BigInteger

fun main(args:Array<String>) {

     val modules = arrayListOf(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61)
     val decimalWidth = 10
     var x = 1604460
     var xRNS = convertToRNS(x, modules)
     var y = 4186182
     var yRNS = convertToRNS(y, modules)

     println("X: ${xRNS}")
     println("Y: ${yRNS}")

     val intermediateProduct = getIntermediateProduct(xRNS, yRNS, modules)
     println("Intermediate product: ${intermediateProduct}")
     val mrnConversionParameters = getMRNConversionParameters(intermediateProduct, modules)
     val mrnElementSum = sumMRNElements(mrnConversionParameters, modules)


 }

 fun convertToRNS(number: Int, modules: ArrayList<Int>): ArrayList<Int> {
     var result = arrayListOf<Int>()

     for (i in 0 until modules.size) {
         result.add(number % modules[i])
     }

     return ArrayList(result.reversed())
 }

 fun getIntermediateProduct(x: ArrayList<Int>, y: ArrayList<Int>, modules: ArrayList<Int>): ArrayList<Int> {
     var intermediateProduct = arrayListOf<Int>()
     var reversedModules = modules.asReversed()

     for (i in 0 until modules.size) {

         intermediateProduct.add((x[i] * y[i]) % reversedModules[i])
     }

     return intermediateProduct
 }

 fun getMRNConversionParameters(intermediateProduct: ArrayList<Int>, modules: ArrayList<Int>): ArrayList<BigInteger> {
     var reversedIntermediateProduct = intermediateProduct.reversed()
     var mrnParameters = arrayListOf<BigInteger>()

     // 1st parameter is the same as value of x[0]
     mrnParameters.add(0, reversedIntermediateProduct[0].toBigInteger())

     // Iterate over all modules to gea parameter for each digit in number
     for (i in 1 until modules.size) {

         var currentModulesProduct: BigInteger = modules[0].toBigInteger()
         var formulaFirstPart: BigInteger
         var formulaSecondPart: BigInteger

         when(i) {

             1 -> {
                 formulaFirstPart = findConstantForFormula(modules[0].toBigInteger(), modules[i].toBigInteger())

             }

             else -> {
                 for (j in 1 until i) {
                     currentModulesProduct *= modules[j].toBigInteger()
                 }
                 formulaFirstPart = findConstantForFormula(currentModulesProduct, modules[i].toBigInteger())

             }
         }


         formulaSecondPart = formulaFirstPart % modules[i].toBigInteger()

         // Calculate multiplier for second part of formula
         var formulaSecondPartMultiplier = reversedIntermediateProduct[i].toBigInteger()

         for (j in 0 until i) {
             formulaSecondPartMultiplier = formulaSecondPartMultiplier - mrnParameters[j]
         }

         // Savecalculated parameter
         mrnParameters.add(( formulaSecondPart * formulaSecondPartMultiplier ) % modules[i].toBigInteger())
         println("    => MRN PARAM $i: ${mrnParameters.last()}")
     }

     return mrnParameters
 }

 // Solves equation to find inverse additive of a number
 fun findConstantForFormula(pi: BigInteger, pn: BigInteger): BigInteger {
     var x: BigInteger = BigInteger.ZERO

     while (((pi * x) % pn) != BigInteger.ONE) {
         x++
     }
     return x
 }

 fun sumMRNElements(a: ArrayList<BigInteger>, modules: ArrayList<Int>) {

     var intermediateResult: BigInteger = BigInteger.ONE
     var resultMRN: BigInteger = BigInteger.ZERO

     for (i in 0 until modules.size) {

         when(i) {
             0 -> {}
             else -> {
                 intermediateResult = intermediateResult * modules[i - 1].toBigInteger()
             }
         }

         resultMRN = resultMRN + intermediateResult * a[i]

     }

     println("Result of multiplication in MRN: ${resultMRN}")
     convertMRNtoDecimal(resultMRN, modules)
 }

 fun convertMRNtoRNS(number: BigInteger, modules: ArrayList<Int>): String {
     var result: String = ""

     for (i in 0 until modules.size) {
         result += number % modules[i].toBigInteger()
     }

     return result.reversed()
 }

 fun convertMRNtoDecimal(mrnNumber: BigInteger, modules: ArrayList<Int>) {
     var modulesProduct = BigInteger.ONE
     var x = arrayListOf<BigInteger>()
     var dividedModulesProduct = arrayListOf<BigInteger>()

     modules.forEach {
         modulesProduct = modulesProduct * it.toBigInteger()
     }

     for (i in 0 until modules.size) {

         x.add(i, BigInteger.ZERO)
         dividedModulesProduct.add( modulesProduct / modules[i].toBigInteger())

         while (((dividedModulesProduct[i] * x[i]) % modules[i].toBigInteger()) != BigInteger.ONE) {
             x[i]++
         }
     }

     var rnsNumber = convertMRNtoRNS(mrnNumber, modules)
     var result: BigInteger = BigInteger.ZERO

     for (j in 0 until modules.size) {
         var number = rnsNumber[j].toInt() - 48
         result = result + (dividedModulesProduct[j] * number.toBigInteger() * x[j])

     }

     result = result % modulesProduct

     println("Decimal value: $result")
 }
