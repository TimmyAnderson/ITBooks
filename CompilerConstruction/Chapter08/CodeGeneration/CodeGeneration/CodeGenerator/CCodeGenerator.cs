using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCodeGenerator
	{
//-------------------------------------------------------------------------------------------------------
		private static readonly string							EXIT_LABEL_NAME="_EXIT";
		private static readonly string							BEFORE_ELSE_LABEL_KEY="BEFORE_ELSE";
		private static readonly string							AFTER_ELSE_LABEL_KEY="AFTER_ELSE";
		private static readonly string							AFTER_IF_LABEL_KEY="AFTER_IF";
		private static readonly string							BEFORE_WHILE_LABEL_KEY="BEFORE_WHILE";
		private static readonly string							AFTER_WHILE_LABEL_KEY="AFTER_WHILE";
		private static readonly string							BEFORE_ELSE_LABEL_NAME="BEFORE_ELSE_";
		private static readonly string							AFTER_ELSE_LABEL_NAME="AFTER_ELSE_";
		private static readonly string							AFTER_IF_LABEL_NAME="AFTER_IF_";
		private static readonly string							BEFORE_WHILE_LABEL_NAME="BEFORE_WHILE_";
		private static readonly string							AFTER_WHILE_LABEL_NAME="AFTER_WHILE_";
		private static readonly string							TRUE_LABEL_NAME="TRUE_";
		private static readonly string							FALSE_LABEL_NAME="FALSE_";
//-------------------------------------------------------------------------------------------------------
		private static readonly string							NAME_EXPRESSION="EXPRESSION";
		private static readonly string							NAME_ARGS="ARGS";
		private static readonly string							NAME_VARIABLE="VARIABLE";
		private static readonly string							NAME_COMPARE_OPERATION="COMPARE_OPERATION";
		private static readonly string							NAME_ADD_OPERATION="ADD_OPERATION";
		private static readonly string							NAME_MUL_OPERATION="MUL_OPERATION";
		private static readonly string							NAME_CALL="CALL";
		private static readonly string							NAME_ID="TerminalID";
		private static readonly string							NAME_TERMINAL_IF="TerminalIF";
		private static readonly string							NAME_TERMINAL_ELSE="TerminalELSE";
		private static readonly string							NAME_TERMINAL_WHILE="TerminalWHILE";
		private static readonly string							NAME_LESSER="TerminalLesser";
		private static readonly string							NAME_LESSER_OR_EQUAL="TerminalLesserOrEqual";
		private static readonly string							NAME_GREATER="TerminalGreater";
		private static readonly string							NAME_GREATER_OR_EQUAL="TerminalGreaterOrEqual";
		private static readonly string							NAME_EQUAL="TerminalEqual";
		private static readonly string							NAME_NOT_EQUAL="TerminalNotEqual";
		private static readonly string							NAME_TERMINAL_PLUS="TerminalPlus";
		private static readonly string							NAME_TERMINAL_ASTERISK="TerminalAsterisk";
		private static readonly string							NAME_STRING_LITERAL="TerminalString";
		private static readonly string							NAME_NUMBER="TerminalNumber";
//-------------------------------------------------------------------------------------------------------
		private readonly CStringLiterals						MStringLiterals;
		private readonly CSymbolTableData_Variable[]			MGlobalVariables;
		private readonly CInstructionCollection					MInstructions;
		private readonly Dictionary<string,int>					MLabelCounter;
		private readonly StringBuilder							MLog;
//-------------------------------------------------------------------------------------------------------
		private CSymbolTable									MCurrentTable;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCodeGenerator(CSymbolTable RootTable, CStringLiterals StringLiterals, CSymbolTableData_Variable[] GlobalVariables)
		{
			MInstructions=new CInstructionCollection();
			MLabelCounter=new Dictionary<string,int>();
			MLog=new StringBuilder();
		
			MCurrentTable=RootTable;
			MStringLiterals=StringLiterals;
			MGlobalVariables=GlobalVariables;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Log
		{
			get
			{
				return(MLog.ToString());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void DefaultPreOrderAction(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine(Node.Symbol.Name);
		}
//-------------------------------------------------------------------------------------------------------
		private int IncrementLabelCounter(string FunctionName)
		{
			if (MLabelCounter.ContainsKey(FunctionName)==true)
			{
				int												LabelCounter=++MLabelCounter[FunctionName];

				return(LabelCounter);
			}
			else
			{
				MLabelCounter.Add(FunctionName,1);

				return(1);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private string ConvertStringLiteral(string StringLiteral)
		{
			StringBuilder										SB=new StringBuilder();

			for(int i=0;i<StringLiteral.Length;i++)
			{
				char											Char=StringLiteral[i];

				if (Char=='\\')
				{
					char										NextChar=StringLiteral[i+1];

					if (NextChar=='n')
					{
						SB.Append("\"");
						SB.Append(",");
						SB.Append("13");
						SB.Append(",");
						SB.Append("10");
						SB.Append(",");
						SB.Append("\"");
						i++;
					}
					else if (NextChar=='\\')
					{
						SB.Append("\\");
						i+=2;
					}
					else if (NextChar=='"')
					{
						SB.Append("\"");
						SB.Append(",");
						SB.Append("34");
						SB.Append(",");
						SB.Append("\"");
						i++;
					}
					else
					{
						throw(new InvalidOperationException("Invalid LITERAL !"));
					}
				}
				else
				{
					SB.Append(Char);
				}
			}

			string												Text=SB.ToString();

			Text=Text.Replace(",\"\"","");
			Text=Text.Replace("\"\",","");

			return(Text);
		}
//-------------------------------------------------------------------------------------------------------
		private void AddInstruction(CInstruction Instruction)
		{
			MInstructions.AddInstruction(Instruction);

			MLog.AppendLine(string.Format("ADDED INSTRUCTION: [{0}] !",Instruction.GetInstructionString(false)));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;].
		private void TraversePostOrderAction_VARIABLE_DECLARATION_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - VARIABLE_DECLARATION_Choice2 POST !");

			// Ziska MENO VARIABLE.
			CParseTreeNode										TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier									TokenID=(CToken_Identifier) TreeNodeID.Token;
			string												SymbolName=TokenID.Lexema;

			// Zisti ci VARIABLE 'id' je deklarovana.
			if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
			{
				CSymbolTableItem								SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);
				CSymbolTableData_Variable						Variable=(CSymbolTableData_Variable) SymbolFromSymbolTable.SymbolTableData;
				ESymbolType										SymbolType=Variable.SymbolType;

				// Globalne premenne su inicializovane v metode GenerateCode().
				if (Variable.IsGlobalVariable==true)
				{
					return;
				}

				CInstruction_POP								Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Gets value of constant for variable [{0}] to EAX.",SymbolName));

				AddInstruction(Instruction_POP);

				int												StackOffset=SymbolFromSymbolTable.StackOffset;

				CInstruction_MOV								Instruction_MOV=new CInstruction_MOV(new COperand_Memory(ERegister.E_R_EBP,StackOffset),new COperand_Register(ERegister.E_R_EAX),string.Format("[VARIABLE_DECLARATION -> TYPE_SPECIFIER id=CONST;] - Moves value of constant for variable [{0}] to STACK.",SymbolName));

				AddInstruction(Instruction_MOV);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Can't find SYMBOL for NAME [{0}] !",SymbolName)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT].
		private void TraversePreOrderAction_FUNCTION_DECLARATION(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - FUNCTION_DECLARATION PRE !");

			CParseTreeNode										TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			string												FunctionName=TreeNodeID.Token.Lexema;

			CInstruction_PROC									Instruction_PROC=new CInstruction_PROC(FunctionName,string.Format("[VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Begins procedure [{0}()].",FunctionName));

			AddInstruction(Instruction_PROC);

			CInstruction_PUSH									Instruction_PUSH1=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EBP),string.Format("[VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBP to STACK."));

			AddInstruction(Instruction_PUSH1);

			CInstruction_PUSH									Instruction_PUSH2=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EBX),string.Format("[VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Stores original value of EBX to STACK."));

			AddInstruction(Instruction_PUSH2);

			CInstruction_MOV									Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EBP),new COperand_Register(ERegister.E_R_ESP),string.Format("[VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Moves ESP to EBP to store begin address of LOCAL VARIABLES."));

			AddInstruction(Instruction_MOV);

			// Nastavi SYMBOL TABLE na SYMBOL TABLE reprezentujucu NOVY SCOPE.
			MCurrentTable=MCurrentTable.MoveToNextChildScopeTableIndex();

			// Vypocitam miesto pre LOKALNE PREMENNE.
			int													TotalStackSize=MCurrentTable.CalculateSubNodesTotalStackSize();

			// Alokacia miesta na STACKU pre LOKALNE PREMENNE.
			CInstruction_SUB									Instruction_SUB=new CInstruction_SUB(new COperand_Register(ERegister.E_R_ESP),new COperand_Constant(TotalStackSize),string.Format("[VARIABLE -> [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT]] - Allocates memory for local variables."));

			AddInstruction(Instruction_SUB);

			// !!! Doplnim kod pre RUNTIME FUNKCIE.
			if (FunctionName=="PrintInt")
			{
				AddInstruction(new CInstruction_ASM_TEXT("MOV EAX,[EBP+12]",string.Format("Moves ADDRESS of INTEGER VALUE to EAX.")));
				AddInstruction(new CInstruction_ASM_TEXT("INVOKE wsprintf, OFFSET _ConversionBuffer, OFFSET _ConversionString, EAX",string.Format("Calls wsprintf() to fill BUFFER with INTEGER VALUE.")));
				AddInstruction(new CInstruction_ASM_TEXT("print OFFSET _ConversionBuffer",string.Format("Prints INTEGER VALUE to CONSOLE.")));
			}
			else if (FunctionName=="PrintLineInt")
			{
				AddInstruction(new CInstruction_ASM_TEXT("MOV EAX,[EBP+12]",string.Format("Moves ADDRESS of INTEGER VALUE to EAX.")));
				AddInstruction(new CInstruction_ASM_TEXT("INVOKE wsprintf, OFFSET _ConversionBuffer, OFFSET _ConversionString, EAX",string.Format("Calls wsprintf() to fill BUFFER with INTEGER VALUE.")));
				AddInstruction(new CInstruction_ASM_TEXT("print OFFSET _ConversionBuffer",string.Format("Prints INTEGER VALUE to CONSOLE.")));
				AddInstruction(new CInstruction_ASM_TEXT("print OFFSET _EmptyLine",string.Format("Prints EMPTY LINE to CONSOLE.")));
			}
			else if (FunctionName=="PrintString")
			{
				AddInstruction(new CInstruction_ASM_TEXT("MOV EAX,[EBP+12]",string.Format("Moves ADDRESS of STRING VALUE to EAX.")));
				AddInstruction(new CInstruction_ASM_TEXT("print EAX",string.Format("Prints STRING VALUE to CONSOLE.")));
			}
			else if (FunctionName=="PrintLineString")
			{
				AddInstruction(new CInstruction_ASM_TEXT("MOV EAX,[EBP+12]",string.Format("Moves ADDRESS of STRING VALUE to EAX.")));
				AddInstruction(new CInstruction_ASM_TEXT("print EAX",string.Format("Prints STRING VALUE to CONSOLE.")));
				AddInstruction(new CInstruction_ASM_TEXT("print OFFSET _EmptyLine",string.Format("Prints EMPTY LINE to CONSOLE.")));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FUNCTION_DECLARATION -> TYPE_SPECIFIER id(PARAMS) COMPOUND_STATEMENT].
		private void TraversePostOrderAction_FUNCTION_DECLARATION(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - FUNCTION_DECLARATION POST !");

			// Nastavi SYMBOL TABLE na PARENT SYMBOL TABLE reprezentujucu PREDCHADZAJUCI SCOPE.
			MCurrentTable=MCurrentTable.ParentScopeTable;
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}].
		private void TraversePreOrderAction_COMPOUND_STATEMENT(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - COMPOUND_STATEMENT PRE !");

			// Nastavi SYMBOL TABLE na SYMBOL TABLE reprezentujucu NOVY SCOPE.
			MCurrentTable=MCurrentTable.MoveToNextChildScopeTableIndex();
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [COMPOUND_STATEMENT -> {LOCAL_DECLARATIONS STATEMENT_LIST}].
		private void TraversePostOrderAction_COMPOUND_STATEMENT(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - COMPOUND_STATEMENT POST !");

			// Nastavi SYMBOL TABLE na PARENT SYMBOL TABLE reprezentujucu PREDCHADZAJUCI SCOPE.
			MCurrentTable=MCurrentTable.ParentScopeTable;

			if ((MCurrentTable is CSymbolTable_FunctionDeclaration)==true)
			{
				CSymbolTable_FunctionDeclaration				Function=(CSymbolTable_FunctionDeclaration) MCurrentTable;
				string											FunctionName=Function.FunctionName;

				CInstruction_LABEL								Instruction_LABEL=new CInstruction_LABEL(string.Format("{0}{1}",FunctionName,EXIT_LABEL_NAME),string.Format("[COMPOUND_STATEMENT -> {{LOCAL_DECLARATIONS STATEMENT_LIST}}] - Label to procedure [{0}()] exit code.",FunctionName));

				AddInstruction(Instruction_LABEL);

				// Dealokacia miesta na STACKU pre LOKALNE PREMENNE.
				// !!! Robi sa PRESUNOM registra EBP do ESP, kedze v EBP je hodnota STACK POINTER PRED ALOKACIOU LOKALNYCH PREMENNYCH.
				CInstruction_MOV								Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_ESP),new COperand_Register(ERegister.E_R_EBP),string.Format("[COMPOUND_STATEMENT -> {{LOCAL_DECLARATIONS STATEMENT_LIST}}] - Deallocates memory of local variables."));

				AddInstruction(Instruction_MOV);

				CInstruction_POP								Instruction_POP1=new CInstruction_POP(ERegister.E_R_EBX,string.Format("[COMPOUND_STATEMENT -> {{LOCAL_DECLARATIONS STATEMENT_LIST}}] - Restores original value of EBX."));

				AddInstruction(Instruction_POP1);

				CInstruction_POP								Instruction_POP2=new CInstruction_POP(ERegister.E_R_EBP,string.Format("[COMPOUND_STATEMENT -> {{LOCAL_DECLARATIONS STATEMENT_LIST}}] - Restores original value of EBP."));

				AddInstruction(Instruction_POP2);

				CInstruction_RET								Instruction_RET=new CInstruction_RET(FunctionName,string.Format("[COMPOUND_STATEMENT -> {{LOCAL_DECLARATIONS STATEMENT_LIST}}] - Exits procedure [{0}()].",FunctionName));

				AddInstruction(Instruction_RET);

				CInstruction_ENDP								Instruction_ENDP=new CInstruction_ENDP(FunctionName,string.Format("[COMPOUND_STATEMENT -> {{LOCAL_DECLARATIONS STATEMENT_LIST}}] - Ends procedure [{0}()].",FunctionName));

				AddInstruction(Instruction_ENDP);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;].
		private void TraversePostOrderAction_EXPRESSION_STATEMENT_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - EXPRESSION_STATEMENT_Choice1 POST !");

			// Vyberiem hodnotu EXPRESSION zo STACK.
			CInstruction_POP									Instruction_POP_OperandRight=new CInstruction_POP(ERegister.E_R_EBX,string.Format("[EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets value of EXPRESSION for operation ASSIGNMENT to EBX."));

			AddInstruction(Instruction_POP_OperandRight);

			// Vyberiem ADRESU VARIABLE zo STACK.
			CInstruction_POP									Instruction_POP_OperandLeft=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Gets address of VARIABLE for operation ASSIGNMENT to EAX."));

			AddInstruction(Instruction_POP_OperandLeft);

			// Priradim do VARIABLE hodnotu EXPRESSION.
			// !!! Po tejto instrukcii sa uz do STACK NESMIE NIC ZARADIT, kedze sa jedna o operaciu PRIRADENIA ukocenu znakom BODKOCIARKA.
			CInstruction_MOV									Instruction_MOV=new CInstruction_MOV(new COperand_Memory(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBX),string.Format("[EXPRESSION_STATEMENT -> VARIABLE=EXPRESSION;] - Moves value of EXPRESSION to VARIABLE."));

			AddInstruction(Instruction_MOV);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [EXPRESSION_STATEMENT -> CALL;].
		private void TraversePostOrderAction_EXPRESSION_STATEMENT_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - EXPRESSION_STATEMENT_Choice2 POST !");

			CParseTreeNode										CALL=Node.GetChildTreeNodeBySymbolName(NAME_CALL,0);
			CParseTreeNode										TreeNodeID=CALL.GetChildTreeNodeBySymbolName(NAME_ID,0);
			string												FunctionName=TreeNodeID.Token.Lexema;

			CSymbolTableItem									FunctionSymbolItem=MCurrentTable.GetSymbolFromCurrentOrParentScopes(FunctionName);

			if ((FunctionSymbolItem.SymbolTableData is CSymbolTableData_Function)==true)
			{
				CSymbolTableData_Function						TypedFunctionSymbolItem=(CSymbolTableData_Function) FunctionSymbolItem.SymbolTableData;

				// Zistim, ci FUNKCIA ma nejaku RETURN VALUE.
				if (TypedFunctionSymbolItem.FunctionReturnType!=ESymbolType.E_ST_VOID)
				{
					// Vyberiem vysledok volania FUNCTION zo STACK.
					// !!! Po tejto instrukcii sa uz do STACK NESMIE NIC ZARADIT, kedze sa jedna o operaciu VOLANIA FUNCTION ukocenu znakom BODKOCIARKA.
					CInstruction_POP							Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[EXPRESSION_STATEMENT -> CALL;] - Removes UNUSED RETURN VALUE from STACK."));

					AddInstruction(Instruction_POP);
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT].
		private void TraversePreOrderAction_SELECTION_STATEMENT_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - SELECTION_STATEMENT_Choice1 PRE !");

			CParseTreeNode										TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);

			CSymbolTable_FunctionDeclaration					Function=MCurrentTable.GetFunctionSymbolTableInCurrentOrParentScope();
			string												FunctionName=Function.FunctionName;

			int													LabelCounter=IncrementLabelCounter(FunctionName);

			string												AfterIfLabelName=string.Format("{0}{1}_{2}",AFTER_IF_LABEL_NAME,FunctionName,LabelCounter);

			TERMINAL_IF.SetCodeGenerationProperty(AFTER_IF_LABEL_KEY,AfterIfLabelName);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT].
		private void TraverseInPostOrderAction_SELECTION_STATEMENT_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem, CParseTreeNode ChildNode)
		{
			MLog.AppendLine("CODE GENERATOR - SELECTION_STATEMENT_Choice1 IN-POST !");

			CParseTreeNode										TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);

			if (ChildNode.Symbol.Name==NAME_EXPRESSION)
			{
				CInstruction_POP					 			Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Gets value of EXPRESSION to EAX."));

				AddInstruction(Instruction_POP);

				CInstruction_CMP					 			Instruction_CMP=new CInstruction_CMP(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(0),string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0."));

				AddInstruction(Instruction_CMP);

				string											LabelNameAfterIf=TERMINAL_IF.GetCodeGenerationProperty(AFTER_IF_LABEL_KEY);

				CInstruction_JE					 				Instruction_JE=new CInstruction_JE(LabelNameAfterIf,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - If value of EXPRESSION==0, jumps to END of IF block."));

				AddInstruction(Instruction_JE);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT].
		private void TraversePostOrderAction_SELECTION_STATEMENT_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - SELECTION_STATEMENT_Choice1 POST !");

			CParseTreeNode										TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);

			string												AfterIfLabelName=TERMINAL_IF.GetCodeGenerationProperty(AFTER_IF_LABEL_KEY);

			CInstruction_LABEL					 				Instruction_LABEL=new CInstruction_LABEL(AfterIfLabelName,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT] - Label to END of IF block."));

			AddInstruction(Instruction_LABEL);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT].
		private void TraversePreOrderAction_SELECTION_STATEMENT_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - SELECTION_STATEMENT_Choice2 PRE !");

			CParseTreeNode										TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);

			CSymbolTable_FunctionDeclaration					Function=MCurrentTable.GetFunctionSymbolTableInCurrentOrParentScope();
			string												FunctionName=Function.FunctionName;

			int													LabelCounter=IncrementLabelCounter(FunctionName);

			string												BeforeElseLabelName=string.Format("{0}{1}_{2}",BEFORE_ELSE_LABEL_NAME,FunctionName,LabelCounter);
			string												AfterElseLabelName=string.Format("{0}{1}_{2}",AFTER_ELSE_LABEL_NAME,FunctionName,LabelCounter);

			TERMINAL_IF.SetCodeGenerationProperty(BEFORE_ELSE_LABEL_KEY,BeforeElseLabelName);
			TERMINAL_IF.SetCodeGenerationProperty(AFTER_ELSE_LABEL_KEY,AfterElseLabelName);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT].
		private void TraverseInPostOrderAction_SELECTION_STATEMENT_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem, CParseTreeNode ChildNode)
		{
			MLog.AppendLine("CODE GENERATOR - SELECTION_STATEMENT_Choice2 IN-POST !");

			CParseTreeNode										TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);

			if (ChildNode.Symbol.Name==NAME_EXPRESSION)
			{
				CInstruction_POP					 			Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Gets value of EXPRESSION to EAX."));

				AddInstruction(Instruction_POP);

				CInstruction_CMP					 			Instruction_CMP=new CInstruction_CMP(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(0),string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Compares value of EXPRESSION to 0."));

				AddInstruction(Instruction_CMP);

				string											LabelNameBeforeElse=TERMINAL_IF.GetCodeGenerationProperty(BEFORE_ELSE_LABEL_KEY);

				CInstruction_JE					 				Instruction_JE=new CInstruction_JE(LabelNameBeforeElse,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - If value of EXPRESSION==0, jumps to ELSE block."));

				AddInstruction(Instruction_JE);
			}
			else if (ChildNode.Symbol.Name==NAME_TERMINAL_ELSE)
			{
				string											LabelNameAfterElse=TERMINAL_IF.GetCodeGenerationProperty(AFTER_ELSE_LABEL_KEY);

				CInstruction_JMP					 			Instruction_JMP=new CInstruction_JMP(LabelNameAfterElse,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Jumps to END of ELSE block."));

				AddInstruction(Instruction_JMP);

				string											LabelNameBeforeElse=TERMINAL_IF.GetCodeGenerationProperty(BEFORE_ELSE_LABEL_KEY);

				CInstruction_LABEL					 			Instruction_LABEL=new CInstruction_LABEL(LabelNameBeforeElse,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to BEGIN of ELSE block."));

				AddInstruction(Instruction_LABEL);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT].
		private void TraversePostOrderAction_SELECTION_STATEMENT_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - SELECTION_STATEMENT_Choice2 POST !");

			CParseTreeNode										TERMINAL_IF=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_IF,0);

			string												AfterElseLabelName=TERMINAL_IF.GetCodeGenerationProperty(AFTER_ELSE_LABEL_KEY);

			CInstruction_LABEL					 				Instruction_LABEL=new CInstruction_LABEL(AfterElseLabelName,string.Format("[SELECTION_STATEMENT -> if (EXPRESSION) STATEMENT else STATEMENT] - Label to END of ELSE block."));

			AddInstruction(Instruction_LABEL);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT].
		private void TraversePreOrderAction_ITERATION_STATEMENT(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - ITERATION_STATEMENT PRE !");

			CParseTreeNode										TERMINAL_WHILE=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_WHILE,0);

			CSymbolTable_FunctionDeclaration					Function=MCurrentTable.GetFunctionSymbolTableInCurrentOrParentScope();
			string												FunctionName=Function.FunctionName;

			int													LabelCounter=IncrementLabelCounter(FunctionName);

			string												BeforeWhileLabelName=string.Format("{0}{1}_{2}",BEFORE_WHILE_LABEL_NAME,FunctionName,LabelCounter);
			string												AfterWhileLabelName=string.Format("{0}{1}_{2}",AFTER_WHILE_LABEL_NAME,FunctionName,LabelCounter);

			TERMINAL_WHILE.SetCodeGenerationProperty(BEFORE_WHILE_LABEL_KEY,BeforeWhileLabelName);
			TERMINAL_WHILE.SetCodeGenerationProperty(AFTER_WHILE_LABEL_KEY,AfterWhileLabelName);

			CInstruction_LABEL					 				Instruction_LABEL=new CInstruction_LABEL(BeforeWhileLabelName,string.Format("[ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to BEGIN of WHILE block."));

			AddInstruction(Instruction_LABEL);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT].
		private void TraverseInPostOrderAction_ITERATION_STATEMENT(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem, CParseTreeNode ChildNode)
		{
			MLog.AppendLine("CODE GENERATOR - ITERATION_STATEMENT IN-POST !");

			CParseTreeNode										TERMINAL_WHILE=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_WHILE,0);

			if (ChildNode.Symbol.Name==NAME_EXPRESSION)
			{
				CInstruction_POP					 			Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Gets value of EXPRESSION to EAX."));

				AddInstruction(Instruction_POP);

				CInstruction_CMP					 			Instruction_CMP=new CInstruction_CMP(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(0),string.Format("[ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Compares value of EXPRESSION to 0."));

				AddInstruction(Instruction_CMP);

				string											LabelNameAfterWhile=TERMINAL_WHILE.GetCodeGenerationProperty(AFTER_WHILE_LABEL_KEY);

				CInstruction_JE					 				Instruction_JE=new CInstruction_JE(LabelNameAfterWhile,string.Format("[ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block."));

				AddInstruction(Instruction_JE);
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT].
		private void TraversePostOrderAction_ITERATION_STATEMENT(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - ITERATION_STATEMENT POST !");

			CParseTreeNode										TERMINAL_WHILE=Node.GetChildTreeNodeBySymbolName(NAME_TERMINAL_WHILE,0);

			string												LabelNameBeforeWhile=TERMINAL_WHILE.GetCodeGenerationProperty(BEFORE_WHILE_LABEL_KEY);

			CInstruction_JMP					 				Instruction_JMP=new CInstruction_JMP(LabelNameBeforeWhile,string.Format("[ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Jumps to end of WHILE block."));

			AddInstruction(Instruction_JMP);

			string												LabelNameAfterWhile=TERMINAL_WHILE.GetCodeGenerationProperty(AFTER_WHILE_LABEL_KEY);

			CInstruction_LABEL					 				Instruction_LABEL=new CInstruction_LABEL(LabelNameAfterWhile,string.Format("[ITERATION_STATEMENT -> while (EXPRESSION) STATEMENT] - Label to END of WHILE block."));

			AddInstruction(Instruction_LABEL);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [RETURN_STATEMENT -> return;].
		private void TraversePostOrderAction_RETURN_STATEMENT_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - RETURN_STATEMENT_Choice1 POST !");

			CSymbolTable_FunctionDeclaration					Function=MCurrentTable.GetFunctionSymbolTableInCurrentOrParentScope();
			string												FunctionName=Function.FunctionName;
			
			CInstruction_JMP									Instruction_JMP=new CInstruction_JMP(string.Format("{0}{1}",FunctionName,EXIT_LABEL_NAME),string.Format("[RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [{0}] exit code.",FunctionName));

			AddInstruction(Instruction_JMP);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [RETURN_STATEMENT -> return(EXPRESSION);].
		private void TraversePostOrderAction_RETURN_STATEMENT_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - RETURN_STATEMENT_Choice2 POST !");

			CParseTreeNode										EXPRESSION=Node.GetChildTreeNodeBySymbolName(NAME_EXPRESSION,0);
			CSymbolTable_FunctionDeclaration					Function=MCurrentTable.GetFunctionSymbolTableInCurrentOrParentScope();
			string												FunctionName=Function.FunctionName;

			CInstruction_POP									Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[RETURN_STATEMENT -> return(EXPRESSION);] - Gets function [{0}] result to EAX.",FunctionName));

			AddInstruction(Instruction_POP);

			CInstruction_JMP									Instruction_JMP=new CInstruction_JMP(string.Format("{0}{1}",FunctionName,EXIT_LABEL_NAME),string.Format("[RETURN_STATEMENT -> return(EXPRESSION);] - Jumps to function [{0}] exit code.",FunctionName));

			AddInstruction(Instruction_JMP);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE -> id].
		private void TraversePostOrderAction_VARIABLE_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - VARIABLE_Choice1 POST !");

			// Ziska MENO VARIABLE.
			CParseTreeNode										TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier									TokenID=(CToken_Identifier) TreeNodeID.Token;
			string												SymbolName=TokenID.Lexema;

			// Zisti ci VARIABLE 'id' je deklarovana.
			if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
			{
				CSymbolTableItem								SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);
				CSymbolTableData_Variable						Variable=(CSymbolTableData_Variable) SymbolFromSymbolTable.SymbolTableData;
				ESymbolType										SymbolType=Variable.SymbolType;

				if (SymbolType==ESymbolType.E_ST_INT || SymbolType==ESymbolType.E_ST_STRING)
				{
					// Lokalna premenna, alebo parameter.
					if (Variable.IsGlobalVariable==false)
					{
						int										StackOffset=SymbolFromSymbolTable.StackOffset;

						CInstruction_MOV						Instruction_MOV_StackPointer=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBP),string.Format("[VARIABLE -> id] - Moves EBP for local variable array [{0}] to EAX.",SymbolName));

						AddInstruction(Instruction_MOV_StackPointer);

						// EAX bude obsahovat adresu premennej.
						CInstruction_ADD						Instruction_ADD_Offset=new CInstruction_ADD(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(StackOffset),string.Format("[VARIABLE -> id] - Adds offset for symbol [{0}] to EAX. Now EAX contains address of symbol [{0}].",SymbolName));

						AddInstruction(Instruction_ADD_Offset);
					}
					// Globalna premenna.
					else
					{
						CInstruction_MOV						Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_MemoryOffset(SymbolName),string.Format("Moves ADDRESS of [{0}] to EAX.",SymbolName));

						AddInstruction(Instruction_MOV);
					}

					// Ulozi adresu ID na STACK.
					CInstruction_PUSH							Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[VARIABLE -> id] - Pushs address of variable [{0}] to STACK.",SymbolName));

					AddInstruction(Instruction_PUSH);
				}
				else if (SymbolType==ESymbolType.E_ST_INT_ARRAY || SymbolType==ESymbolType.E_ST_STRING_ARRAY)
				{
					if (Variable.IsGlobalVariable==false)
					{
						if ((Variable is CSymbolTableData_Param)==true)
						{
							int									StackOffset=SymbolFromSymbolTable.StackOffset;
							
							// EAX bude obsahovat adresu POLA.
							CInstruction_MOV					Instruction_MOV_StackPointer=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Memory(ERegister.E_R_EBP,StackOffset),string.Format("[VARIABLE -> id] - Moves array base address [EBP+StackOffset] for parameter array [{0}] to EAX.",SymbolName));

							AddInstruction(Instruction_MOV_StackPointer);
						}
						else
						{
							int									StackOffset=SymbolFromSymbolTable.StackOffset;

							CInstruction_MOV					Instruction_MOV_StackPointer=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBP),string.Format("[VARIABLE -> id] - Moves EBP for local variable array [{0}] to EAX.",SymbolName));

							AddInstruction(Instruction_MOV_StackPointer);

							// EAX bude obsahovat adresu POLA.
							CInstruction_ADD					Instruction_ADD_Offset=new CInstruction_ADD(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(StackOffset),string.Format("[VARIABLE -> id] - Adds local variable offset for local variable array [{0}] to EAX. Now EAX contains base array address of array [{0}].",SymbolName));

							AddInstruction(Instruction_ADD_Offset);
						}
					}
					// Globalna premenna.
					else
					{
						// EAX bude obsahovat adresu POLA.
						CInstruction_MOV						Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_MemoryOffset(SymbolName),string.Format("[VARIABLE -> id] - Moves base array address for global variable array [{0}] to EAX.",SymbolName));

						AddInstruction(Instruction_MOV);
					}

					// Ulozi adresu ID na STACK.
					CInstruction_PUSH							Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[VARIABLE -> id] - Pushs address of variable [{0}] to STACK.",SymbolName));

					AddInstruction(Instruction_PUSH);
				}
				else
				{
					throw(new InvalidOperationException(string.Format("Invalid TYPE for SYMBOL [{0}] !",SymbolName)));
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Can't find SYMBOL for NAME [{0}] !",SymbolName)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [VARIABLE -> id[EXPRESSION]].
		private void TraversePostOrderAction_VARIABLE_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - VARIABLE_Choice2 POST !");

			// Ziska MENO VARIABLE.
			CParseTreeNode										TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier									TokenID=(CToken_Identifier) TreeNodeID.Token;
			string												SymbolName=TokenID.Lexema;

			// Zisti ci VARIABLE 'id' je deklarovana.
			if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
			{
				CSymbolTableItem								SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);
				CSymbolTableData_Variable						Variable=(CSymbolTableData_Variable) SymbolFromSymbolTable.SymbolTableData;
				ESymbolType										SymbolType=Variable.SymbolType;

				if (SymbolType==ESymbolType.E_ST_INT_ARRAY || SymbolType==ESymbolType.E_ST_STRING_ARRAY)
				{
					ESymbolType									NonArraySymbolType=SymbolType.EXT_GetNonArraySymbolType();
					int											NonArraySymbolTypeSizeof=NonArraySymbolType.EXT_GetSizeof(EVariableType.E_VT_VALUE);

					// Do EAX ulozim hodnotu EXPRESSION.
					CInstruction_POP							Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[VARIABLE -> id[EXPRESSION]] - Pops value of EXPRESSION for array [{0}] to EAX.",SymbolName));

					AddInstruction(Instruction_POP);

					// Do EXB ulozim SIZEOF(ITEM).
					CInstruction_MOV							Instruction_MOV_Sizeof=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EBX),new COperand_Constant(NonArraySymbolTypeSizeof),string.Format("[VARIABLE -> id[EXPRESSION]] - Moves SIZEOF(ARRAY_ITEM) for array [{0}] to EBX.",SymbolName));

					AddInstruction(Instruction_MOV_Sizeof);

					// Vynasobim EXPRESSION*SIZEOF(ITEM).
					CInstruction_MUL							Instruction_MUL=new CInstruction_MUL(new COperand_Register(ERegister.E_R_EBX),string.Format("[VARIABLE -> id[EXPRESSION]] - Multiplies EXPRESSION*SIZEOF(ARRAY_ITEM) to calculate array index byte offset for array [{0}].",SymbolName));

					AddInstruction(Instruction_MUL);

					// Ulozim EXPRESSION*SIZEOF(ITEM) do EBX.
					CInstruction_MOV							Instruction_MOV_Offset=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EBX),new COperand_Register(ERegister.E_R_EAX),string.Format("[VARIABLE -> id[EXPRESSION]] - Moves array index byte offset EXPRESSION*SIZEOF(ARRAY_ITEM) for array [{0}] to EBX.",SymbolName));

					AddInstruction(Instruction_MOV_Offset);

					// Lokalna premenna, alebo parameter.
					if (Variable.IsGlobalVariable==false)
					{
						if ((Variable is CSymbolTableData_Param)==true)
						{
							int									StackOffset=SymbolFromSymbolTable.StackOffset;
							
							// EAX bude obsahovat adresu POLA.
							CInstruction_MOV					Instruction_MOV_StackPointer=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Memory(ERegister.E_R_EBP,StackOffset),string.Format("[VARIABLE -> id[EXPRESSION]] - Moves array base address [EBP+StackOffset] for parameter array [{0}] to EAX.",SymbolName));

							AddInstruction(Instruction_MOV_StackPointer);
						}
						else
						{
							int									StackOffset=SymbolFromSymbolTable.StackOffset;

							CInstruction_MOV					Instruction_MOV_StackPointer=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBP),string.Format("[VARIABLE -> id[EXPRESSION]] - Moves EBP for local variable array [{0}] to EAX.",SymbolName));

							AddInstruction(Instruction_MOV_StackPointer);

							// EAX bude obsahovat adresu POLA.
							CInstruction_ADD					Instruction_ADD_Offset=new CInstruction_ADD(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(StackOffset),string.Format("[VARIABLE -> id[EXPRESSION]] - Adds local variable offset for local variable array [{0}] to EAX. Now EAX contains base array address of array [{0}].",SymbolName));

							AddInstruction(Instruction_ADD_Offset);
						}
					}
					// Globalna premenna.
					else
					{
						// EAX bude obsahovat adresu POLA.
						CInstruction_MOV						Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_MemoryOffset(SymbolName),string.Format("[VARIABLE -> id[EXPRESSION]] - Moves base array address for global variable array [{0}] to EAX.",SymbolName));

						AddInstruction(Instruction_MOV);
					}

					// Prida BYTE OFFSET do EAX na vypocet adresy ID[EXPRESSION].
					CInstruction_ADD							Instruction_ADD=new CInstruction_ADD(new COperand_Register(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBX),string.Format("[VARIABLE -> id[EXPRESSION]] - Adds array index byt offset for array [{0}] to EAX. Now EAX contains address of [{0}[EXPRESSION]].",SymbolName));

					AddInstruction(Instruction_ADD);

					// Ulozi adresu ID[EXPRESSION] na STACK.
					CInstruction_PUSH							Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[VARIABLE -> id[EXPRESSION]] - Pushs address of variable [{0}[EXPRESSION]] to STACK.",SymbolName));

					AddInstruction(Instruction_PUSH);
				}
				else
				{
					throw(new InvalidOperationException(string.Format("Invalid TYPE for SYMBOL [{0}] !",SymbolName)));
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Can't find SYMBOL for NAME [{0}] !",SymbolName)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION].
		private void TraversePostOrderAction_EXPRESSION_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - EXPRESSION_Choice1 POST !");

			CParseTreeNode										COMPARE_OPERATION=Node.GetChildTreeNodeBySymbolName(NAME_COMPARE_OPERATION,0);

			// Vyberiem RIGHT OPERAND zo STACK.
			CInstruction_POP									Instruction_POP_OperandRight=new CInstruction_POP(ERegister.E_R_EBX,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O2 for operation COMPARE to EBX."));

			AddInstruction(Instruction_POP_OperandRight);

			// Vyberiem LEFT OPERAND zo STACK.
			CInstruction_POP									Instruction_POP_OperandLeft=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Gets OPERAND O1 for operation COMPARE to EAX."));

			AddInstruction(Instruction_POP_OperandLeft);

			// Vykonam porovnanie O1 a O2
			CInstruction_CMP									Instruction_CMP=new CInstruction_CMP(new COperand_Register(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBX),string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Compares O1 to O2."));

			AddInstruction(Instruction_CMP);

			CSymbolTable_FunctionDeclaration					Function=MCurrentTable.GetFunctionSymbolTableInCurrentOrParentScope();
			string												FunctionName=Function.FunctionName;

			int													LabelCounter=IncrementLabelCounter(FunctionName);

			string												TrueLabelName=string.Format("{0}{1}_{2}",TRUE_LABEL_NAME,FunctionName,LabelCounter);
			string												FalseLabelName=string.Format("{0}{1}_{2}",FALSE_LABEL_NAME,FunctionName,LabelCounter);

			if (COMPARE_OPERATION.ChildNodes.Length>0)
			{
				CParseTreeNode									COMPARE_SYMBOL=COMPARE_OPERATION.ChildNodes[0];
				CSymbol											Symbol=COMPARE_SYMBOL.Symbol;

				if (Symbol.Name==NAME_LESSER)
				{
					// Podmieneny JUMP na TRUE.
					CInstruction_JL								Instruction_JB=new CInstruction_JL(TrueLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<O2."));

					AddInstruction(Instruction_JB);
				}
				else if (Symbol.Name==NAME_LESSER_OR_EQUAL)
				{
					// Podmieneny JUMP na TRUE.
					CInstruction_JLE							Instruction_JNA=new CInstruction_JLE(TrueLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1<=O2"));

					AddInstruction(Instruction_JNA);
				}
				else if (Symbol.Name==NAME_GREATER)
				{
					// Podmieneny JUMP na TRUE.
					CInstruction_JG								Instruction_JG=new CInstruction_JG(TrueLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>O2"));

					AddInstruction(Instruction_JG);
				}
				else if (Symbol.Name==NAME_GREATER_OR_EQUAL)
				{
					// Podmieneny JUMP na TRUE.
					CInstruction_JGE							Instruction_JNB=new CInstruction_JGE(TrueLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1>=O2"));

					AddInstruction(Instruction_JNB);
				}
				else if (Symbol.Name==NAME_EQUAL)
				{
					// Podmieneny JUMP na TRUE.
					CInstruction_JE								Instruction_JE=new CInstruction_JE(TrueLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1==O2"));

					AddInstruction(Instruction_JE);
				}
				else if (Symbol.Name==NAME_NOT_EQUAL)
				{
					// Podmieneny JUMP na TRUE.
					CInstruction_JNE							Instruction_JNE=new CInstruction_JNE(TrueLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to TRUE label if O1!=O2"));

					AddInstruction(Instruction_JNE);
				}
				else
				{
					throw(new InvalidOperationException("BNF RULE [COMPARE_OPERATION -> <= | < | > | >= | == | !=] contains INVALID SYMBOL !"));
				}
			}
			else
			{
				throw(new InvalidOperationException("BNF RULE [COMPARE_OPERATION -> <= | < | > | >= | == | !=] has INVALID number of CHILD NODES !"));
			}

			// MOVE pre FALSE.
			CInstruction_MOV									Instruction_MOVE_FALSE=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(0),string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves FALSE value (0) to EAX."));

			AddInstruction(Instruction_MOVE_FALSE);

			// JUMP na FALSE.
			CInstruction_JMP									Instruction_JMP=new CInstruction_JMP(FalseLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Jumps to FALSE label."));

			AddInstruction(Instruction_JMP);

			// LABEL pre TRUE.
			CInstruction_LABEL									Instruction_LABEL_TRUE=new CInstruction_LABEL(TrueLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label TRUE."));

			AddInstruction(Instruction_LABEL_TRUE);

			// MOVE pre TRUE.
			CInstruction_MOV									Instruction_MOVE_TRUE=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(1),string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Moves TRUE value (1) to EAX."));

			AddInstruction(Instruction_MOVE_TRUE);

			// LABEL pre FALSE.
			CInstruction_LABEL									Instruction_LABEL_FALSE=new CInstruction_LABEL(FalseLabelName,string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Label FALSE."));

			AddInstruction(Instruction_LABEL_FALSE);

			// !!! Kazdy vysledok musi byt ulozeny do STACK.
			CInstruction_PUSH									Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[EXPRESSION -> ADDITIVE_EXPRESSION COMPARE_OPERATION ADDITIVE_EXPRESSION] - Pushs result of operation COMPARE to STACK."));

			AddInstruction(Instruction_PUSH);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM].
		private void TraversePostOrderAction_ADDITIVE_EXPRESSION_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - ADDITIVE_EXPRESSION_Choice1 POST !");
			
			CParseTreeNode										ADD_OPERATION=Node.GetChildTreeNodeBySymbolName(NAME_ADD_OPERATION,0);
			CParseTreeNode										PLUS=ADD_OPERATION.GetChildTreeNodeBySymbolNameOrNULL(NAME_TERMINAL_PLUS,0);
			bool												IsPlus=false;

			if (PLUS!=null)
			{
				IsPlus=true;
			}

			// Vyberiem RIGHT OPERAND zo STACK.
			CInstruction_POP									Instruction_POP_OperandRight=new CInstruction_POP(ERegister.E_R_EBX,string.Format("[ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O2 for operation [{0}] to EBX.",(IsPlus==true) ? "ADDITION" : "SUBTRACTION"));

			AddInstruction(Instruction_POP_OperandRight);

			// Vyberiem LEFT OPERAND zo STACK.
			CInstruction_POP									Instruction_POP_OperandLeft=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Gets OPERAND O1 for operation [{0}] to EAX.",(IsPlus==true) ? "ADDITION" : "SUBTRACTION"));

			AddInstruction(Instruction_POP_OperandLeft);

			if (IsPlus==true)
			{
				CInstruction_ADD								Instruction_ADD=new CInstruction_ADD(new COperand_Register(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBX),string.Format("[ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX+EBX."));

				AddInstruction(Instruction_ADD);
			}
			else
			{
				CInstruction_SUB								Instruction_SUB=new CInstruction_SUB(new COperand_Register(ERegister.E_R_EAX),new COperand_Register(ERegister.E_R_EBX),string.Format("[ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Executes operation EAX=EAX-EBX."));

				AddInstruction(Instruction_SUB);
			}

			// !!! Kazdy vysledok musi byt ulozeny do STACK.
			CInstruction_PUSH									Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[ADDITIVE_EXPRESSION -> ADDITIVE_EXPRESSION ADD_OPERATION TERM] - Pushs operation result to STACK."));

			AddInstruction(Instruction_PUSH);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [TERM -> TERM MUL_OPERATION FACTOR].
		private void TraversePostOrderAction_TERM_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - TERM_Choice1 POST !");

			CParseTreeNode										MUL_OPERATION=Node.GetChildTreeNodeBySymbolName(NAME_MUL_OPERATION,0);
			CParseTreeNode										ASTERISK=MUL_OPERATION.GetChildTreeNodeBySymbolNameOrNULL(NAME_TERMINAL_ASTERISK,0);
			bool												IsMultiplication=false;

			if (ASTERISK!=null)
			{
				IsMultiplication=true;
			}

			// Vyberiem RIGHT OPERAND zo STACK.
			CInstruction_POP									Instruction_POP_OperandRight=new CInstruction_POP(ERegister.E_R_EBX,string.Format("[TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O2 for operation [{0}] to EBX.",(IsMultiplication==true) ? "MULTIPLICATION" : "DIVISION"));

			AddInstruction(Instruction_POP_OperandRight);

			// Vyberiem LEFT OPERAND zo STACK.
			CInstruction_POP									Instruction_POP_OperandLeft=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[TERM -> TERM MUL_OPERATION FACTOR] - Gets OPERAND O1 for operation [{0}] to EAX.",(IsMultiplication==true) ? "MULTIPLICATION" : "DIVISION"));

			AddInstruction(Instruction_POP_OperandLeft);

			if (IsMultiplication==true)
			{
				CInstruction_IMUL								Instruction_ADD=new CInstruction_IMUL(new COperand_Register(ERegister.E_R_EBX),string.Format("[TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EDX:EAX=EAX*EBX."));

				AddInstruction(Instruction_ADD);
			}
			else
			{
				// !!! Pred instrukciou IDIV je NUTNE konvertovat hodnotou EAX na EDX:EAX, inak moze dojst k UNDERFLOW, alebo OVERFLOW.
				CInstruction_CDQ								Instruction_CDQ=new CInstruction_CDQ(string.Format("[TERM -> TERM MUL_OPERATION FACTOR] - Converts EAX to EDX:EAX."));

				AddInstruction(Instruction_CDQ);

				CInstruction_IDIV								Instruction_DIV=new CInstruction_IDIV(new COperand_Register(ERegister.E_R_EBX),string.Format("[TERM -> TERM MUL_OPERATION FACTOR] - Executes operation EAX=EDX:EAX/EBX."));

				AddInstruction(Instruction_DIV);
			}

			// !!! Kazdy vysledok musi byt ulozeny do STACK.
			CInstruction_PUSH									Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[TERM -> TERM MUL_OPERATION FACTOR] - Pushs operation result to STACK."));

			AddInstruction(Instruction_PUSH);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> VARIABLE].
		private void TraversePostOrderAction_FACTOR_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - FACTOR_Choice2 POST !");

			CParseTreeNode										VARIABLE=Node.GetChildTreeNodeBySymbolName(NAME_VARIABLE,0);
			CParseTreeNode										TreeNodeID=VARIABLE.GetChildTreeNodeBySymbolName(NAME_ID,0);
			CToken_Identifier									TokenID=(CToken_Identifier) TreeNodeID.Token;
			string												SymbolName=TokenID.Lexema;

			// Zisti ci VARIABLE 'id' je deklarovana.
			if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(SymbolName)==true)
			{
				// !!! Ak sa v CHILD NODES NEVYSKYTUJE EXPRESSION potom sa pozaduje ADRESA POLA a NIE HODNOTA jeho ITEM.
				CParseTreeNode									EXPRESSION=VARIABLE.GetChildTreeNodeBySymbolNameOrNULL(NAME_EXPRESSION,0);

				CSymbolTableItem								SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(SymbolName);
				CSymbolTableData_Variable						Variable=(CSymbolTableData_Variable) SymbolFromSymbolTable.SymbolTableData;
				ESymbolType										SymbolType=Variable.SymbolType;

				// !!!!! Premenna je POLE, ktore sa prenasa do FUNKCIE (CHILD NODE je [VARIABLE -> id] a NIE [VARIABLE -> id[EXPRESSION]]).
				if (EXPRESSION==null && (SymbolType==ESymbolType.E_ST_INT_ARRAY || SymbolType==ESymbolType.E_ST_STRING_ARRAY || SymbolType==ESymbolType.E_ST_VOID_ARRAY))
				{
					// !!!!! NEROBI sa NIC, lebo premenna sa prenasa ADRESOU a ta UZ JE na STACKU.
				}
				else
				{
					// Vyberiem adresu premennej zo STACK.
					CInstruction_POP							Instruction_POP=new CInstruction_POP(ERegister.E_R_EAX,string.Format("[VARIABLE -> [FACTOR -> VARIABLE]] - Gets address of variable [{0}] to EAX.",SymbolName));

					AddInstruction(Instruction_POP);

					// Ziskam hodnotu z adresu premennej.
					CInstruction_MOV							Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Memory(ERegister.E_R_EAX),string.Format("[VARIABLE -> [FACTOR -> VARIABLE]] - Moves value of variable [{0}] from address of variable.",SymbolName));

					AddInstruction(Instruction_MOV);

					// Ulozim hodnotu premennej na STACK.
					CInstruction_PUSH							Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[VARIABLE -> [FACTOR -> VARIABLE]] - Puts value of variable [{0}] to STACK.",SymbolName));

					AddInstruction(Instruction_PUSH);
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("Can't find SYMBOL for NAME [{0}] !",SymbolName)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> num].
		private void TraversePostOrderAction_FACTOR_Choice4(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - FACTOR_Choice4 POST !");

			CParseTreeNode										NUMBER=Node.GetChildTreeNodeBySymbolName(NAME_NUMBER,0);
			CToken												Token=NUMBER.Token;
			string												Lexema=Token.Lexema;

			int													Value=int.Parse(Lexema);

			CInstruction_MOV									Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(Value),string.Format("[FACTOR -> num] - Moves INT constant to EAX."));

			AddInstruction(Instruction_MOV);

			// Ulozim adresu NUMBER na STACK.
			CInstruction_PUSH									Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[FACTOR -> num] - Pushs INT constant to STACK."));

			AddInstruction(Instruction_PUSH);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [FACTOR -> string_literal].
		private void TraversePostOrderAction_FACTOR_Choice5(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - FACTOR_Choice5 POST !");

			CParseTreeNode										STRING_LITERAL=Node.GetChildTreeNodeBySymbolName(NAME_STRING_LITERAL,0);
			CToken												Token=STRING_LITERAL.Token;
			string												StringLiteral=Token.Lexema;

			string												StringLiteralID=MStringLiterals.GetIDForLiteral(StringLiteral);

			// Ulozim adresu STRING LITERAL na STACK.
			CInstruction_PUSH									Instruction_PUSH=new CInstruction_PUSH(new COperand_MemoryOffset(StringLiteralID),string.Format("[FACTOR -> string_literal] - Pushs address of LITERAL to STACK."));

			AddInstruction(Instruction_PUSH);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [CALL -> id(ARGS)].
		private void TraversePostOrderAction_CALL(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - CALL POST !");

			CParseTreeNode										ARGS=Node.GetChildTreeNodeBySymbolName(NAME_ARGS,0);

			// Zisti ParamTypes pre ARGS.
			CParseTreeNodeData_ParamTypes						ParamTypes=ARGS.GetTreeNodeData<CParseTreeNodeData_ParamTypes>();

			if (ParamTypes!=null)
			{
				CParseTreeNodeData_Type[]						FunctionParamTypes=ParamTypes.ParamTypes;
				CParseTreeNode									TreeNodeID=Node.GetChildTreeNodeBySymbolName(NAME_ID,0);
				CToken_Identifier								TokenID=(CToken_Identifier) TreeNodeID.Token;
				string											FunctionName=TokenID.Lexema;

				// Ziska MENO FUNCTION.
				if (MCurrentTable.ContainsSymbolInCurrentOrParentScopes(FunctionName)==true)
				{
					CSymbolTableItem							SymbolFromSymbolTable=MCurrentTable.GetSymbolFromCurrentOrParentScopes(FunctionName);

					// Zisti ci 'id' reprezentuje FUNCTION.
					if ((SymbolFromSymbolTable.SymbolTableData is CSymbolTableData_Function)==true)
					{
						CSymbolTable_FunctionDeclaration		FunctionTable=MCurrentTable.GetFunctionSymbolTable(FunctionName);

						if (FunctionTable!=null)
						{
							CSymbolTableData_Function			TypedSymbolFromSymbolTable=(CSymbolTableData_Function) SymbolFromSymbolTable.SymbolTableData;

							CInstruction_CALL					Instruction_CALL=new CInstruction_CALL(FunctionName,string.Format("[CALL -> id(ARGS)] - Calls procedure [{0}()].",FunctionName));

							AddInstruction(Instruction_CALL);

							int									ParamSize=ParamTypes.GetSizeof(EVariableType.E_VT_POINTER);

							// Vymazem ARGUMENTS zo STACKU posunom registra ESP.
							CInstruction_ADD					Instruction_ADD=new CInstruction_ADD(new COperand_Register(ERegister.E_R_ESP),new COperand_Constant(ParamSize),string.Format("[CALL -> id(ARGS)] - Removes ARGUMENTS of procedure [{0}()] from STACK.",FunctionName));

							AddInstruction(Instruction_ADD);

							// !!! Ak EXISTUJE RETURN VALUE, tak ju ulozim do STACKU. RETURN VALUE je VZDY prenasana cez register EAX.
							if (TypedSymbolFromSymbolTable.FunctionReturnType!=ESymbolType.E_ST_VOID)
							{
								CInstruction_PUSH				Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[CALL -> id(ARGS)] - Pushs RETURN VALUE of procedure [{0}()] to STACK.",FunctionName));

								AddInstruction(Instruction_PUSH);
							}
						}
						else
						{
							throw(new InvalidOperationException(string.Format("Can't FIND FUNCTION TABLE for FUNCTION [{0}] !",FunctionName)));
						}
					}
					else
					{
						throw(new InvalidOperationException(string.Format("NODE doesn't contain VALID FUNCTION DECLARATION !",Node)));
					}
				}
				else
				{
					throw(new InvalidOperationException(string.Format("NODE doesn't contain FUNCTION DECLARATION !",Node)));
				}
			}
			else
			{
				throw(new InvalidOperationException(string.Format("NODE doesn't contain PARAM TYPES INFORMATION !",Node)));
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [CONST -> num].
		private void TraversePostOrderAction_CONST_Choice1(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - CONST_Choice1 POST !");

			// Globalne premenne su inicializovane v metode GenerateCode().
			if ((MCurrentTable is CSymbolTable_Root)==true)
			{
				return;
			}

			CParseTreeNode										NUMBER=Node.GetChildTreeNodeBySymbolName(NAME_NUMBER,0);
			CToken												Token=NUMBER.Token;
			string												Lexema=Token.Lexema;

			int													Value=int.Parse(Lexema);

			CInstruction_MOV									Instruction_MOV=new CInstruction_MOV(new COperand_Register(ERegister.E_R_EAX),new COperand_Constant(Value),string.Format("[CONST -> num] - Moves INT constant to EAX."));

			AddInstruction(Instruction_MOV);

			CInstruction_PUSH									Instruction_PUSH=new CInstruction_PUSH(new COperand_Register(ERegister.E_R_EAX),string.Format("[CONST -> num] - Push INT constant to STACK."));

			AddInstruction(Instruction_PUSH);
		}
//-------------------------------------------------------------------------------------------------------
		// Choice - [CONST -> string_literal].
		private void TraversePostOrderAction_CONST_Choice2(CParseTreeNode Node, CCodeGenerationTraverseItem TraverseItem)
		{
			MLog.AppendLine("CODE GENERATOR - CONST_Choice2 POST !");

			// Globalne premenne su inicializovane v metode GenerateCode().
			if ((MCurrentTable is CSymbolTable_Root)==true)
			{
				return;
			}

			CParseTreeNode										STRING_LITERAL=Node.GetChildTreeNodeBySymbolName(NAME_STRING_LITERAL,0);
			CToken												Token=STRING_LITERAL.Token;
			string												StringLiteral=Token.Lexema;

			string												StringLiteralID=MStringLiterals.GetIDForLiteral(StringLiteral);

			// Ulozim adresu STRING LITERAL na STACK.
			CInstruction_PUSH									Instruction_PUSH=new CInstruction_PUSH(new COperand_MemoryOffset(StringLiteralID),string.Format("[CONST -> string_literal] - Pushs address of LITERAL to STACK."));

			AddInstruction(Instruction_PUSH);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private CCodeGenerationTraverseItemList CreateTraverseItemList(CNonterminalCollection NonterminalCollection)
		{
			CChoice												Choice_VARIABLE_DECLARATION_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE_DECLARATION").First().Choices[1];
			CChoice												Choice_FUNCTION_DECLARATION=NonterminalCollection.Nonterminals.Where(P => P.Name=="FUNCTION_DECLARATION").First().Choices[0];
			CChoice												Choice_COMPOUND_STATEMENT=NonterminalCollection.Nonterminals.Where(P => P.Name=="COMPOUND_STATEMENT").First().Choices[0];
			CChoice												Choice_EXPRESSION_STATEMENT_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="EXPRESSION_STATEMENT").First().Choices[0];
			CChoice												Choice_EXPRESSION_STATEMENT_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="EXPRESSION_STATEMENT").First().Choices[1];
			CChoice												Choice_SELECTION_STATEMENT_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="SELECTION_STATEMENT").First().Choices[0];
			CChoice												Choice_SELECTION_STATEMENT_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="SELECTION_STATEMENT").First().Choices[1];
			CChoice												Choice_ITERATION_STATEMENT=NonterminalCollection.Nonterminals.Where(P => P.Name=="ITERATION_STATEMENT").First().Choices[0];
			CChoice												Choice_RETURN_STATEMENT_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="RETURN_STATEMENT").First().Choices[0];
			CChoice												Choice_RETURN_STATEMENT_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="RETURN_STATEMENT").First().Choices[1];
			CChoice												Choice_VARIABLE_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE").First().Choices[0];
			CChoice												Choice_VARIABLE_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="VARIABLE").First().Choices[1];
			CChoice												Choice_EXPRESSION_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="EXPRESSION").First().Choices[0];
			CChoice												Choice_ADDITIVE_EXPRESSION_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="ADDITIVE_EXPRESSION").First().Choices[0];
			CChoice												Choice_TERM_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="TERM").First().Choices[0];
			CChoice												Choice_FACTOR_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[1];
			CChoice												Choice_FACTOR_Choice4=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[3];
			CChoice												Choice_FACTOR_Choice5=NonterminalCollection.Nonterminals.Where(P => P.Name=="FACTOR").First().Choices[4];
			CChoice												Choice_CALL=NonterminalCollection.Nonterminals.Where(P => P.Name=="CALL").First().Choices[0];
			CChoice												Choice_CONST_Choice1=NonterminalCollection.Nonterminals.Where(P => P.Name=="CONST").First().Choices[0];
			CChoice												Choice_CONST_Choice2=NonterminalCollection.Nonterminals.Where(P => P.Name=="CONST").First().Choices[1];

			CCodeGenerationTraverseItemList						List=new CCodeGenerationTraverseItemList(DefaultPreOrderAction,null,null,null);

			CCodeGenerationTraverseItem							PTTI_VARIABLE_DECLARATION_Choice2=new CCodeGenerationTraverseItem(Choice_VARIABLE_DECLARATION_Choice2,null,null,null,TraversePostOrderAction_VARIABLE_DECLARATION_Choice2);
			CCodeGenerationTraverseItem							PTTI_FUNCTION_DECLARATION=new CCodeGenerationTraverseItem(Choice_FUNCTION_DECLARATION,TraversePreOrderAction_FUNCTION_DECLARATION,null,null,TraversePostOrderAction_FUNCTION_DECLARATION);
			CCodeGenerationTraverseItem							PTTI_COMPOUND_STATEMENT=new CCodeGenerationTraverseItem(Choice_COMPOUND_STATEMENT,TraversePreOrderAction_COMPOUND_STATEMENT,null,null,TraversePostOrderAction_COMPOUND_STATEMENT);
			CCodeGenerationTraverseItem							PTTI_EXPRESSION_STATEMENT_Choice1=new CCodeGenerationTraverseItem(Choice_EXPRESSION_STATEMENT_Choice1,null,null,null,TraversePostOrderAction_EXPRESSION_STATEMENT_Choice1);
			CCodeGenerationTraverseItem							PTTI_EXPRESSION_STATEMENT_Choice2=new CCodeGenerationTraverseItem(Choice_EXPRESSION_STATEMENT_Choice2,null,null,null,TraversePostOrderAction_EXPRESSION_STATEMENT_Choice2);
			CCodeGenerationTraverseItem							PTTI_SELECTION_STATEMENT_Choice1=new CCodeGenerationTraverseItem(Choice_SELECTION_STATEMENT_Choice1,TraversePreOrderAction_SELECTION_STATEMENT_Choice1,null,TraverseInPostOrderAction_SELECTION_STATEMENT_Choice1,TraversePostOrderAction_SELECTION_STATEMENT_Choice1);
			CCodeGenerationTraverseItem							PTTI_SELECTION_STATEMENT_Choice2=new CCodeGenerationTraverseItem(Choice_SELECTION_STATEMENT_Choice2,TraversePreOrderAction_SELECTION_STATEMENT_Choice2,null,TraverseInPostOrderAction_SELECTION_STATEMENT_Choice2,TraversePostOrderAction_SELECTION_STATEMENT_Choice2);
			CCodeGenerationTraverseItem							PTTI_ITERATION_STATEMENT=new CCodeGenerationTraverseItem(Choice_ITERATION_STATEMENT,TraversePreOrderAction_ITERATION_STATEMENT,null,TraverseInPostOrderAction_ITERATION_STATEMENT,TraversePostOrderAction_ITERATION_STATEMENT);
			CCodeGenerationTraverseItem							PTTI_RETURN_STATEMENT_Choice1=new CCodeGenerationTraverseItem(Choice_RETURN_STATEMENT_Choice1,null,null,null,TraversePostOrderAction_RETURN_STATEMENT_Choice1);
			CCodeGenerationTraverseItem							PTTI_RETURN_STATEMENT_Choice2=new CCodeGenerationTraverseItem(Choice_RETURN_STATEMENT_Choice2,null,null,null,TraversePostOrderAction_RETURN_STATEMENT_Choice2);
			CCodeGenerationTraverseItem							PTTI_VARIABLE_Choice1=new CCodeGenerationTraverseItem(Choice_VARIABLE_Choice1,null,null,null,TraversePostOrderAction_VARIABLE_Choice1);
			CCodeGenerationTraverseItem							PTTI_VARIABLE_Choice2=new CCodeGenerationTraverseItem(Choice_VARIABLE_Choice2,null,null,null,TraversePostOrderAction_VARIABLE_Choice2);
			CCodeGenerationTraverseItem							PTTI_EXPRESSION_Choice1=new CCodeGenerationTraverseItem(Choice_EXPRESSION_Choice1,null,null,null,TraversePostOrderAction_EXPRESSION_Choice1);
			CCodeGenerationTraverseItem							PTTI_ADDITIVE_EXPRESSION_Choice1=new CCodeGenerationTraverseItem(Choice_ADDITIVE_EXPRESSION_Choice1,null,null,null,TraversePostOrderAction_ADDITIVE_EXPRESSION_Choice1);
			CCodeGenerationTraverseItem							PTTI_TERM_Choice1=new CCodeGenerationTraverseItem(Choice_TERM_Choice1,null,null,null,TraversePostOrderAction_TERM_Choice1);
			CCodeGenerationTraverseItem							PTTI_FACTOR_Choice2=new CCodeGenerationTraverseItem(Choice_FACTOR_Choice2,null,null,null,TraversePostOrderAction_FACTOR_Choice2);
			CCodeGenerationTraverseItem							PTTI_FACTOR_Choice4=new CCodeGenerationTraverseItem(Choice_FACTOR_Choice4,null,null,null,TraversePostOrderAction_FACTOR_Choice4);
			CCodeGenerationTraverseItem							PTTI_FACTOR_Choice5=new CCodeGenerationTraverseItem(Choice_FACTOR_Choice5,null,null,null,TraversePostOrderAction_FACTOR_Choice5);
			CCodeGenerationTraverseItem							PTTI_CALL=new CCodeGenerationTraverseItem(Choice_CALL,null,null,null,TraversePostOrderAction_CALL);
			CCodeGenerationTraverseItem							PTTI_CONST_Choice1=new CCodeGenerationTraverseItem(Choice_CONST_Choice1,null,null,null,TraversePostOrderAction_CONST_Choice1);
			CCodeGenerationTraverseItem							PTTI_CONST_Choice2=new CCodeGenerationTraverseItem(Choice_CONST_Choice2,null,null,null,TraversePostOrderAction_CONST_Choice2);

			List.AddTraverseItem(PTTI_VARIABLE_DECLARATION_Choice2);
			List.AddTraverseItem(PTTI_FUNCTION_DECLARATION);
			List.AddTraverseItem(PTTI_COMPOUND_STATEMENT);
			List.AddTraverseItem(PTTI_EXPRESSION_STATEMENT_Choice1);
			List.AddTraverseItem(PTTI_EXPRESSION_STATEMENT_Choice2);
			List.AddTraverseItem(PTTI_SELECTION_STATEMENT_Choice1);
			List.AddTraverseItem(PTTI_SELECTION_STATEMENT_Choice2);
			List.AddTraverseItem(PTTI_ITERATION_STATEMENT);
			List.AddTraverseItem(PTTI_RETURN_STATEMENT_Choice1);
			List.AddTraverseItem(PTTI_RETURN_STATEMENT_Choice2);
			List.AddTraverseItem(PTTI_VARIABLE_Choice1);
			List.AddTraverseItem(PTTI_VARIABLE_Choice2);
			List.AddTraverseItem(PTTI_EXPRESSION_Choice1);
			List.AddTraverseItem(PTTI_ADDITIVE_EXPRESSION_Choice1);
			List.AddTraverseItem(PTTI_TERM_Choice1);
			List.AddTraverseItem(PTTI_FACTOR_Choice2);
			List.AddTraverseItem(PTTI_FACTOR_Choice4);
			List.AddTraverseItem(PTTI_FACTOR_Choice5);
			List.AddTraverseItem(PTTI_CALL);
			List.AddTraverseItem(PTTI_CONST_Choice1);
			List.AddTraverseItem(PTTI_CONST_Choice2);

			return(List);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void GenerateCode(CNonterminalCollection NonterminalCollection, CParseTreeNode RootParseTreeNode, CInstructionCollection Instructions)
		{
			MLog.Clear();
			MInstructions.Clear();
			MCurrentTable.ResetChildScopeTableIndex();
			RootParseTreeNode.ClearCodeGenerationProperties();
			MLabelCounter.Clear();

			CCodeGenerationTraverseItemList						TraverseList=CreateTraverseItemList(NonterminalCollection);

			AddInstruction(new CInstruction_ASM_TEXT(".486",null));
			AddInstruction(new CInstruction_ASM_TEXT(".model flat, stdcall",null));
			AddInstruction(new CInstruction_ASM_TEXT("option casemap :none",null));
			AddInstruction(new CInstruction_ASM_TEXT(null,null));
			AddInstruction(new CInstruction_ASM_TEXT("include include\\windows.inc",null));
			AddInstruction(new CInstruction_ASM_TEXT("include macros\\macros.asm",null));
			AddInstruction(new CInstruction_ASM_TEXT(null,null));
			AddInstruction(new CInstruction_ASM_TEXT("include include\\masm32.inc",null));
			AddInstruction(new CInstruction_ASM_TEXT("include include\\user32.inc",null));
			AddInstruction(new CInstruction_ASM_TEXT("include include\\kernel32.inc",null));
			AddInstruction(new CInstruction_ASM_TEXT(null,null));
			AddInstruction(new CInstruction_ASM_TEXT("includelib masm32.lib",null));
			AddInstruction(new CInstruction_ASM_TEXT("includelib user32.lib",null));
			AddInstruction(new CInstruction_ASM_TEXT("includelib kernel32.lib",null));
			AddInstruction(new CInstruction_ASM_TEXT(null,null));

			AddInstruction(new CInstruction_ASM_TEXT(".DATA",null));

			string[]											StringLiterals=MStringLiterals.GetAllLiterals();

			foreach(string StringLiteral in StringLiterals)
			{
				string											ID=MStringLiterals.GetIDForLiteral(StringLiteral);
				string											Value;

				if (StringLiteral!="\"\"")
				{
					Value=string.Format("{0},0",ConvertStringLiteral(StringLiteral));
				}
				else
				{
					Value=string.Format("0",ConvertStringLiteral(StringLiteral));
				}

				string											ASMText=string.Format("{0} BYTE {1}",ID,Value);

				AddInstruction(new CInstruction_ASM_TEXT(ASMText,null));
			}

			foreach(CSymbolTableData_Variable Variable in MGlobalVariables)
			{
				string											VariableName=Variable.SymbolName;
				string											VariableType=Variable.SymbolType.EXT_GetCodeGenerationTypeName();

				if (Variable.SymbolType==ESymbolType.E_ST_INT)
				{
					int											ConstValue=0;

					if (Variable.ConstValue!=null)
					{
						ConstValue=(int) Variable.ConstValue;
					}

					string										Declaration=string.Format("{0} {1} {2}",VariableName,VariableType,ConstValue);

					AddInstruction(new CInstruction_ASM_TEXT(Declaration,null));
				}
				else if (Variable.SymbolType==ESymbolType.E_ST_STRING)
				{

					if (Variable.ConstValue!=null)
					{
						string									ConstValue=(string) Variable.ConstValue;
						string									ID=MStringLiterals.GetIDForLiteral(ConstValue);
						string									Declaration=string.Format("{0} {1} OFFSET {2}",VariableName,VariableType,ID);

						AddInstruction(new CInstruction_ASM_TEXT(Declaration,null));
					}
					else
					{
						string									Declaration=string.Format("{0} {1} 0",VariableName,VariableType);

						AddInstruction(new CInstruction_ASM_TEXT(Declaration,null));
					}
				}
				else if (Variable.SymbolType==ESymbolType.E_ST_INT_ARRAY)
				{
					string										Declaration=string.Format("{0} {1}",VariableName,VariableType);
					CSymbolTableData_ArrayVariable				ArrayVariable=(CSymbolTableData_ArrayVariable) Variable;
					int											ArraySize=ArrayVariable.ArraySize;

					// Alokujem pamat pre pole.
					for(int i=0;i<ArraySize;i++)
					{
						if (i==0)
						{
							Declaration=string.Format("{0} 0",Declaration);
						}
						else
						{
							Declaration=string.Format("{0},0",Declaration);
						}
					}

					AddInstruction(new CInstruction_ASM_TEXT(Declaration,null));
				}
				else if (Variable.SymbolType==ESymbolType.E_ST_STRING_ARRAY)
				{
					string										Declaration=string.Format("{0} {1}",VariableName,VariableType);
					CSymbolTableData_ArrayVariable				ArrayVariable=(CSymbolTableData_ArrayVariable) Variable;
					int											ArraySize=ArrayVariable.ArraySize;

					// Alokujem pamat pre pole.
					for(int i=0;i<ArraySize;i++)
					{
						if (i==0)
						{
							Declaration=string.Format("{0} 0",Declaration);
						}
						else
						{
							Declaration=string.Format("{0},0",Declaration);
						}
					}

					AddInstruction(new CInstruction_ASM_TEXT(Declaration,null));
				}
				else
				{
					throw(new InvalidOperationException("INVALID TYPE of GLOBAL VARIABLE !"));
				}
			}

			AddInstruction(new CInstruction_ASM_TEXT("_ConversionBuffer BYTE 0,0,0,0,0,0,0,0,0,0,0,0,0,0","Buffer for INT to STRING conversion !"));
			AddInstruction(new CInstruction_ASM_TEXT("_ConversionString BYTE \"%d\",0","Conversion string for INT to STRING conversion !"));
			AddInstruction(new CInstruction_ASM_TEXT("_EmptyLine BYTE 13,10,0","Empty line string !"));

			AddInstruction(new CInstruction_ASM_TEXT(null,null));

			AddInstruction(new CInstruction_ASM_TEXT(".CODE",null));
			AddInstruction(new CInstruction_ASM_TEXT(null,null));

			AddInstruction(new CInstruction_ASM_TEXT("Code:",null));
			AddInstruction(new CInstruction_ASM_TEXT("CALL Main",null));
			AddInstruction(new CInstruction_ASM_TEXT("INVOKE ExitProcess,0",null));
			AddInstruction(new CInstruction_ASM_TEXT(null,null));

			RootParseTreeNode.TraverseForCodeGeneration(TraverseList);

			AddInstruction(new CInstruction_ASM_TEXT(null,null));
			AddInstruction(new CInstruction_ASM_TEXT("END Code",null));

			Instructions.FillInstructions(MInstructions);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------