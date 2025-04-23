Public Class Form1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Button_Connect.Visible = True
        Button_Disconnect.Visible = False
        Programmerar.Visible = False
        For Each AvailableSerialPorts As String In SerialPort1.GetPortNames()
            ComboBox_AvailableSerialPorts.Items.Add(AvailableSerialPorts)
            SerialPort1.ReadTimeout = 4000
            Button_Connect.Visible = True
            Button_Disconnect.Visible = False
            Update()
        Next
        ComboBox_AvailableSerialPorts.Text = "Välj Seriell port"
        TextBox_ReceivedMessage.ScrollBars = ScrollBars.Vertical
    End Sub

    Private Sub Button_Connect_Click(sender As Object, e As EventArgs) Handles Button_Connect.Click
        If (ComboBox_AvailableSerialPorts.Text = "Välj Seriell port") Then
            Porttext.Visible = True
        Else
            Porttext.Visible = False
            Button_Connect.Visible = False
            Button_Disconnect.Visible = True
            Programmed.Visible = False
            SerialPort1.PortName = ComboBox_AvailableSerialPorts.Text()

            If SerialPort1.IsOpen = False Then
                Try
                    SerialPort1.Open()
                    System.Threading.Thread.Sleep(500)
                Catch ex As Exception
                    Porttext.Visible = True
                    Button_Connect.Visible = True
                    Button_Disconnect.Visible = False
                    Programmed.Visible = False
                    SerialPort1.PortName = ComboBox_AvailableSerialPorts.Text()
                    ComboBox_AvailableSerialPorts.Text = "Select Serial Port"

                    GoTo slut
                End Try

                ProgramAspekts.Visible = True
                ProgramIntensity.Visible = True
                ProgramRGB.Visible = True
                LäsAspekt.Visible = True
                LäsIntensitet.Visible = True
                LäsRGB.Visible = True
                Update()
                Timer1.Enabled = True
                Dim Current_configuration As String
                Wait2Connect.Visible = True
                While (SerialPort1.BytesToRead = 0)
                    SerialPort1.WriteLine("C")
                    System.Threading.Thread.Sleep(500)
                End While
                TextBox_ReceivedMessage.Text = "Text från nano inkomit"

                Current_configuration = SerialPort1.ReadLine()
                System.Threading.Thread.Sleep(1500)
                Wait2Connect.Visible = False
                Update()
            End If
        End If
slut:
    End Sub

    Private Sub Button_Disconnect_Click(sender As Object, e As EventArgs) Handles Button_Disconnect.Click
        Dim Outmessage As String
        Outmessage = "RESET"
        SerialPort1.WriteLine(Outmessage)
        OutText.Text = Outmessage
        System.Threading.Thread.Sleep(1000)

        If SerialPort1.IsOpen = True Then
            SerialPort1.Close()
        End If

        TextBox_ReceivedMessage.Text = ""

        A01.Text = "0"
        T01.Text = "0"
        R01.Checked = False

        A02.Text = "0"
        T02.Text = "0"
        R02.Checked = False

        A03.Text = "0"
        T03.Text = "0"
        R03.Checked = False

        A04.Text = "0"
        T04.Text = "0"
        R04.Checked = False

        A05.Text = "0"
        T05.Text = "0"
        R05.Checked = False

        A06.Text = "0"
        T06.Text = "0"
        R06.Checked = False

        A07.Text = "0"
        T07.Text = "0"
        R07.Checked = False

        A08.Text = "0"
        T08.Text = "0"
        R08.Checked = False

        A09.Text = "0"
        T09.Text = "0"
        R09.Checked = False

        A10.Text = "0"
        T10.Text = "0"
        R10.Checked = False

        A11.Text = "0"
        T11.Text = "0"
        R11.Checked = False

        A12.Text = "0"
        T12.Text = "0"
        R12.Checked = False

        A13.Text = "0"
        T13.Text = "0"
        R13.Checked = False

        A14.Text = "0"
        T14.Text = "0"
        R14.Checked = False

        A15.Text = "0"
        T15.Text = "0"
        R15.Checked = False

        A16.Text = "0"
        T16.Text = "0"
        R16.Checked = False

        A17.Text = "0"
        T17.Text = "0"
        R17.Checked = False

        A18.Text = "0"
        T18.Text = "0"
        R18.Checked = False

        A19.Text = "0"
        T19.Text = "0"
        R19.Checked = False

        A20.Text = "0"
        T20.Text = "0"
        R20.Checked = False

        A21.Text = "0"
        T21.Text = "0"
        R21.Checked = False

        A22.Text = "0"
        T22.Text = "0"
        R22.Checked = False

        A23.Text = "0"
        T23.Text = "0"
        R23.Checked = False

        A24.Text = "0"
        T24.Text = "0"
        R24.Checked = False

        A25.Text = "0"
        T25.Text = "0"
        R25.Checked = False

        A26.Text = "0"
        T26.Text = "0"
        R26.Checked = False

        A27.Text = "0"
        T27.Text = "0"
        R27.Checked = False

        A28.Text = "0"
        T28.Text = "0"
        R28.Checked = False

        A29.Text = "0"
        T29.Text = "0"
        R29.Checked = False

        A30.Text = "0"
        T30.Text = "0"
        R30.Checked = False


        A31.Text = "0"
        T31.Text = "0"
        R31.Checked = False

        A32.Text = "0"
        T32.Text = "0"
        R32.Checked = False

        Dayintensity.Text = "0"
        Nightintensity.Text = "0"
        Intensitetsadress.Text = "0"
        Blinkfrq.Text = "0"
        Mörk.Text = "0"
        Ramp.Text = "0"
        VitR.Text = "0"
        VitG.Text = "0"
        VitB.Text = "0"
        RödR.Text = "0"
        RödB.Text = "0"
        RödG.Text = "0"
        GrönR.Text = "0"
        GrönG.Text = "0"
        GrönB.Text = "0"
        OrangeR.Text = "0"
        OrangeG.Text = "0"
        OrangeB.Text = "0"
        Button_Connect.Visible = True
        Button_Disconnect.Visible = False
        Programmed.Visible = False
        ProgramAspekts.Visible = False
        ProgramIntensity.Visible = False
        ProgramRGB.Visible = False
        LäsAspekt.Visible = False
        LäsIntensitet.Visible = False
        LäsRGB.Visible = False
        Update()
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        If SerialPort1.IsOpen = True Then
            If SerialPort1.BytesToRead > 0 Then
                Dim ReceivedMessage As String
                ReceivedMessage = SerialPort1.ReadLine
                TextBox_ReceivedMessage.Text = TextBox_ReceivedMessage.Text + ReceivedMessage + Environment.NewLine
            End If

        End If

    End Sub

    Private Sub OpenFile_Click(sender As Object, e As EventArgs) Handles OpenFile.Click
        Programmed.Visible = False
        REM If SerialPort1.IsOpen = True Then
        REM Program.Visible = True
        REM End If

        Dim OpenFileDialog1 As New OpenFileDialog
        OpenFileDialog1.Title = "Öppna Fil..."
        OpenFileDialog1.Multiselect = False
        OpenFileDialog1.Filter = "Signaldefinitioner *.txt|*.txt"
        OpenFileDialog1.ShowDialog()
        Signalfil.Text = OpenFileDialog1.FileName
        Dim Current_configuration As String
        Current_configuration = My.Computer.FileSystem.ReadAllText(Signalfil.Text)

        OutText.Text = Current_configuration

        Dim A As Int16 = 0
        Dim B As Int16 = 0
        Dim C As Int16 = 0
        Dim teststring As String

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R01.Checked = False Else R01.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T01.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A01.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - B))
        TextBox_ReceivedMessage.Text = Current_configuration

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R02.Checked = False Else R02.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T02.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A02.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R03.Checked = False Else R03.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T03.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A03.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R04.Checked = False Else R04.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T04.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A04.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R05.Checked = False Else R05.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T05.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A05.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R06.Checked = False Else R06.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T06.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A06.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R07.Checked = False Else R07.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T07.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A07.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R08.Checked = False Else R08.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T08.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A08.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R09.Checked = False Else R09.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T09.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A09.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R10.Checked = False Else R10.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T10.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A10.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R11.Checked = False Else R11.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T11.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A11.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R12.Checked = False Else R12.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T12.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A12.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R13.Checked = False Else R13.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T13.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A13.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R14.Checked = False Else R14.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T14.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A14.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R15.Checked = False Else R15.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T15.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A15.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R16.Checked = False Else R16.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T16.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A16.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R17.Checked = False Else R17.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T17.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A17.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R18.Checked = False Else R18.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T18.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A18.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R19.Checked = False Else R19.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T19.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A19.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R20.Checked = False Else R20.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T20.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A20.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R21.Checked = False Else R21.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T21.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A21.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R22.Checked = False Else R22.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T22.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A22.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R23.Checked = False Else R23.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T23.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A23.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R24.Checked = False Else R24.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T24.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A24.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R25.Checked = False Else R25.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T25.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A25.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R26.Checked = False Else R26.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T26.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A26.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R27.Checked = False Else R27.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T27.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A27.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R28.Checked = False Else R28.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T28.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A28.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R29.Checked = False Else R29.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T29.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A29.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R30.Checked = False Else R30.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T30.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A30.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R31.Checked = False Else R31.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T31.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A31.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R32.Checked = False Else R32.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T32.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A32.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)



        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        Dayintensity.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        Nightintensity.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        Intensitetsadress.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        Blinkfrq.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        Mörk.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        Ramp.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        VitR.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        VitB.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        VitG.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        RödR.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        RödG.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        RödB.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        GrönR.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        GrönG.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        GrönB.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        OrangeR.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, ",")
        teststring = Strings.Left(Current_configuration, B - 1)
        OrangeG.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        OrangeB.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)
        Update()
    End Sub

    Private Sub SaveFile_Click(sender As Object, e As EventArgs) Handles SaveFile.Click
        Dim SaveFileDialog1 As New SaveFileDialog
        SaveFileDialog1.Title = "Spara Fil..."
        SaveFileDialog1.Filter = "Signaldefinitioner *.txt|*.txt"
        SaveFileDialog1.ShowDialog()
        Signalfil.Text = SaveFileDialog1.FileName

        If Strings.Len(Signalfil.Text) > 0 Then
            System.IO.File.Create(Signalfil.Text).Dispose()

            Dim file As System.IO.StreamWriter
            file = My.Computer.FileSystem.OpenTextFileWriter(Signalfil.Text, True)
            Dim Nydef As String
            Dim R As String
            If R01.Checked = False Then R = 0 Else R = 1
            Nydef = A01.Text + "," + T01.Text + "," + R + "$"
            If R02.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A02.Text + "," + T02.Text + "," + R + "$"
            If R03.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A03.Text + "," + T03.Text + "," + R + "$"
            If R04.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A04.Text + "," + T04.Text + "," + R + "$"
            If R05.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A05.Text + "," + T05.Text + "," + R + "$"
            If R06.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A06.Text + "," + T06.Text + "," + R + "$"
            If R07.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A07.Text + "," + T07.Text + "," + R + "$"
            If R08.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A08.Text + "," + T08.Text + "," + R + "$"
            If R09.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A09.Text + "," + T09.Text + "," + R + "$"
            If R10.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A10.Text + "," + T10.Text + "," + R + "$"
            If R11.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A11.Text + "," + T11.Text + "," + R + "$"
            If R12.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A12.Text + "," + T12.Text + "," + R + "$"
            If R13.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A13.Text + "," + T13.Text + "," + R + "$"
            If R14.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A14.Text + "," + T14.Text + "," + R + "$"
            If R15.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A15.Text + "," + T15.Text + "," + R + "$"
            If R16.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A16.Text + "," + T16.Text + "," + R + "$"
            If R17.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A17.Text + "," + T17.Text + "," + R + "$"
            If R18.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A18.Text + "," + T18.Text + "," + R + "$"
            If R19.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A19.Text + "," + T19.Text + "," + R + "$"
            If R20.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A20.Text + "," + T20.Text + "," + R + "$"
            If R21.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A21.Text + "," + T21.Text + "," + R + "$"
            If R22.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A22.Text + "," + T22.Text + "," + R + "$"
            If R23.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A23.Text + "," + T23.Text + "," + R + "$"
            If R24.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A24.Text + "," + T24.Text + "," + R + "$"
            If R25.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A25.Text + "," + T25.Text + "," + R + "$"
            If R26.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A26.Text + "," + T26.Text + "," + R + "$"
            If R27.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A27.Text + "," + T27.Text + "," + R + "$"
            If R28.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A28.Text + "," + T28.Text + "," + R + "$"
            If R29.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A29.Text + "," + T29.Text + "," + R + "$"
            If R30.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A30.Text + "," + T30.Text + "," + R + "$"
            If R31.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A31.Text + "," + T31.Text + "," + R + "$"
            If R32.Checked = False Then R = 0 Else R = 1
            Nydef = Nydef + A32.Text + "," + T32.Text + "," + R + "$"
            Nydef = Nydef + Dayintensity.Text + "," + Nightintensity.Text + "," + Intensitetsadress.Text + "," + Blinkfrq.Text + "," + Mörk.Text + "," + Ramp.Text + ","
            Nydef = Nydef + VitR.Text + "," + VitG.Text + "," + VitB.Text + "," + RödR.Text + "," + RödG.Text + "," + RödB.Text + "," + GrönR.Text + "," + GrönG.Text + "," + GrönB.Text + "," + OrangeR.Text + "," + OrangeG.Text + "," + OrangeB.Text + "$"
            file.WriteLine(Nydef)
            file.Close()
        End If
    End Sub

    Private Sub ProgramAspekt_Click(sender As Object, e As EventArgs) Handles ProgramAspekts.Click
        ProgramAspekts.Visible = False
        TextBox_ReceivedMessage.Clear()
        Dim Outmessage As String
        Dim R As String
        Programmerar.Visible = True
        If R01.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA1," + A01.Text + "," + T01.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = 3
        OutText.Text = Outmessage

        If R02.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA2," + A02.Text + "," + T02.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R03.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA3," + A03.Text + "," + T03.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R04.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA4," + A04.Text + "," + T04.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R05.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA5," + A05.Text + "," + T05.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R06.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA6," + A06.Text + "," + T06.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R07.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA7," + A07.Text + "," + T07.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R08.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA8," + A08.Text + "," + T08.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R09.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA9," + A09.Text + "," + T09.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R10.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA10," + A10.Text + "," + T10.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R11.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA11," + A11.Text + "," + T11.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R12.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA12," + A12.Text + "," + T12.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R13.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA13," + A13.Text + "," + T13.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R14.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA14," + A14.Text + "," + T14.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R15.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA15," + A15.Text + "," + T15.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R16.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA16," + A16.Text + "," + T16.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R17.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA17," + A17.Text + "," + T17.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R18.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA18," + A18.Text + "," + T18.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R19.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA19," + A19.Text + "," + T19.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R20.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA20," + A20.Text + "," + T20.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R21.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA21," + A21.Text + "," + T21.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R22.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA22," + A22.Text + "," + T22.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R23.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA23," + A23.Text + "," + T23.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R24.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA24," + A24.Text + "," + T24.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R25.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA25," + A25.Text + "," + T25.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R26.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA26," + A26.Text + "," + T26.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R27.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA27," + A27.Text + "," + T27.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R28.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA28," + A28.Text + "," + T28.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R29.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA29," + A29.Text + "," + T29.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R30.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA30," + A30.Text + "," + T30.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(250)
        Programmerar.Value = Programmerar.Value + 3

        If R31.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA31," + A31.Text + "," + T31.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = Programmerar.Value + 3

        If R32.Checked = False Then R = 0 Else R = 1
        Outmessage = "PA32," + A32.Text + "," + T32.Text + "," + R + "$"
        SerialPort1.WriteLine(Outmessage)
        System.Threading.Thread.Sleep(500)
        Programmerar.Value = 100


        OutText.Text = Outmessage
        System.Threading.Thread.Sleep(1000)
        Programmed.Visible = True
        System.Threading.Thread.Sleep(3000)
        TextBox_ReceivedMessage.Text = ""
        Programmed.Visible = False
        ProgramAspekts.Visible = True
        Programmed.Update()
        Programmerar.Visible = False
    End Sub

    Private Sub ProgramRGB_Click(sender As Object, e As EventArgs) Handles ProgramRGB.Click
        ProgramRGB.Visible = False
        TextBox_ReceivedMessage.Clear()
        Dim Outmessage As String
        Outmessage = "PR"
        Outmessage = Outmessage + VitR.Text + ","
        Outmessage = Outmessage + VitG.Text + ","
        Outmessage = Outmessage + VitB.Text + ","
        Outmessage = Outmessage + RödR.Text + ","
        Outmessage = Outmessage + RödG.Text + ","
        Outmessage = Outmessage + RödB.Text + ","
        Outmessage = Outmessage + GrönR.Text + ","
        Outmessage = Outmessage + GrönG.Text + ","
        Outmessage = Outmessage + GrönB.Text + ","
        Outmessage = Outmessage + OrangeR.Text + ","
        Outmessage = Outmessage + OrangeG.Text + ","
        Outmessage = Outmessage + OrangeB.Text + ","
        SerialPort1.WriteLine(Outmessage)
        OutText.Text = Outmessage
        System.Threading.Thread.Sleep(1000)
        Programmed.Visible = True
        Programmed.Update()
        System.Threading.Thread.Sleep(3000)
        TextBox_ReceivedMessage.Text = ""
        Programmed.Visible = False
        ProgramRGB.Visible = True
    End Sub

    Private Sub LäsAspekt_Click(sender As Object, e As EventArgs) Handles LäsAspekt.Click
        SerialPort1.WriteLine("SA")
        While (SerialPort1.BytesToRead = 0)
            System.Threading.Thread.Sleep(500)
        End While
        Dim Current_configuration As String
        Current_configuration = SerialPort1.ReadLine()
        TextBox_ReceivedMessage.Text = Current_configuration
        Update()
        System.Threading.Thread.Sleep(5000)
        Dim A As Int16 = 0
        Dim B As Int16 = 0
        Dim C As Int16 = 0
        Dim teststring As String

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R01.Checked = False Else R01.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T01.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A01.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - B))
        TextBox_ReceivedMessage.Text = Current_configuration

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R02.Checked = False Else R02.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T02.Text = Mid(teststring, A, 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A02.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R03.Checked = False Else R03.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T03.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A03.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R04.Checked = False Else R04.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T04.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A04.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R05.Checked = False Else R05.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T05.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A05.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R06.Checked = False Else R06.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T06.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A06.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R07.Checked = False Else R07.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T07.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A07.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R08.Checked = False Else R08.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T08.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A08.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R09.Checked = False Else R09.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T09.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A09.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R10.Checked = False Else R10.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T10.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A10.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R11.Checked = False Else R11.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T11.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A11.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R12.Checked = False Else R12.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T12.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A12.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R13.Checked = False Else R13.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T13.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A13.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R14.Checked = False Else R14.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T14.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A14.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R15.Checked = False Else R15.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T15.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A15.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R16.Checked = False Else R16.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T16.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A16.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R17.Checked = False Else R17.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T17.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A17.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R18.Checked = False Else R18.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T18.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A18.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R19.Checked = False Else R19.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T19.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A19.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R20.Checked = False Else R20.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T20.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A20.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R21.Checked = False Else R21.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T21.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A21.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R22.Checked = False Else R22.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T22.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A22.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R23.Checked = False Else R23.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T23.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A23.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R24.Checked = False Else R24.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T24.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A24.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R25.Checked = False Else R25.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T25.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A25.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R26.Checked = False Else R26.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T26.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A26.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R27.Checked = False Else R27.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T27.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A27.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R28.Checked = False Else R28.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T28.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A28.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R29.Checked = False Else R29.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T29.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A29.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R30.Checked = False Else R30.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T30.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A30.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R31.Checked = False Else R31.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T31.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A31.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)

        B = InStr(Current_configuration, "$")
        teststring = Strings.Left(Current_configuration, B - 1)
        A = B - 1
        If Mid(teststring, A, 1) = "0" Then R32.Checked = False Else R32.Checked = True
        teststring = Strings.Left(teststring, A - 2)
        A = A - 2
        C = InStr(Current_configuration, ",")
        T32.Text = Mid(teststring, C + 1, A - C + 1)
        A = C - 1
        teststring = Strings.Left(teststring, A)
        A32.Text = teststring
        Current_configuration = Strings.Right(Current_configuration, Strings.Len(Current_configuration) - B)
    End Sub

    Private Sub LäsRGB_Click(sender As Object, e As EventArgs) Handles LäsRGB.Click
        SerialPort1.WriteLine("SR")
        While (SerialPort1.BytesToRead = 0)
            System.Threading.Thread.Sleep(500)
        End While
        Dim Current_configuration As String
        Current_configuration = SerialPort1.ReadLine()
        TextBox_ReceivedMessage.Text = Current_configuration
        Update()
        System.Threading.Thread.Sleep(1000)
        Dim A As Int16 = 0
        A = InStr(Current_configuration, ",")
        VitR.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        VitG.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        VitB.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        RödR.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        RödG.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        RödB.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        GrönR.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        GrönG.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        GrönB.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        OrangeR.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        OrangeG.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        OrangeB.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

    End Sub

    Private Sub LäsIntensitet_Click(sender As Object, e As EventArgs) Handles LäsIntensitet.Click
        SerialPort1.WriteLine("SI")
        While (SerialPort1.BytesToRead = 0)
            System.Threading.Thread.Sleep(500)
        End While
        Dim Current_configuration As String
        Current_configuration = SerialPort1.ReadLine()
        TextBox_ReceivedMessage.Text = Current_configuration
        Update()
        System.Threading.Thread.Sleep(5000)
        Dim A As Int16 = 0
        A = InStr(Current_configuration, ",")
        Dayintensity.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        Nightintensity.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        Intensitetsadress.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        Blinkfrq.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        Mörk.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

        A = InStr(Current_configuration, ",")
        Ramp.Text = Strings.Left(Current_configuration, A - 1)
        Current_configuration = Strings.Right(Current_configuration, (Strings.Len(Current_configuration) - A))

    End Sub

    Private Sub ProgramIntensity_Click(sender As Object, e As EventArgs) Handles ProgramIntensity.Click
        ProgramIntensity.Visible = False
        TextBox_ReceivedMessage.Clear()
        Dim Outmessage As String
        Outmessage = "PI"
        Outmessage = Outmessage + Dayintensity.Text + ","
        Outmessage = Outmessage + Nightintensity.Text + ","
        Outmessage = Outmessage + Intensitetsadress.Text + ","
        Outmessage = Outmessage + Blinkfrq.Text + ","
        Outmessage = Outmessage + Mörk.Text + ","
        Outmessage = Outmessage + Ramp.Text + ","
        SerialPort1.WriteLine(Outmessage)
        OutText.Text = Outmessage
        System.Threading.Thread.Sleep(1000)
        Programmed.Visible = True
        Programmed.Update()
        System.Threading.Thread.Sleep(3000)
        TextBox_ReceivedMessage.Text = ""
        Programmed.Visible = False
        ProgramIntensity.Visible = True

    End Sub
End Class
