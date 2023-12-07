import subprocess as sub
import yaml
from pprint import pprint
import os

build_dir = "build"

def getResultFromString(output):
    return (output.split(':')[-1]).strip()

def runTestCase(case):
    exec_dir = os.path.join(build_dir, 'expression_evaluator ')
    program = exec_dir + ' "' + case + '"' + '> res.txt'
    sub.run(program, shell = True)
    with open("res.txt", "r") as file:
        output = file.read()
    return getResultFromString(output)

def getTestCasesFromFile():
    filePath = "testCases.yaml"
    with open(filePath, "r") as file:
        testCases = yaml.load(file, Loader=yaml.FullLoader)
    return testCases

def printFailedCase(testCases, case, receivedResult):
    print(case  + " - Failed")
    print("     Expression : " + testCases[case]["expression"])
    print("     Expected : " + testCases[case]["expected"])
    print("     Received : " + receivedResult)

def runAllCases(testCases):
    flag = True
    for testCase in testCases:
        result = runTestCase(testCases[testCase]["expression"])
        if result != testCases[testCase]["expected"]:
            flag = False
            printFailedCase(testCases, testCase, result)
    os.remove("res.txt")
    return flag

testCases = getTestCasesFromFile()
flag = runAllCases(testCases)
if flag == True:
    print("All cases succeeded ")
