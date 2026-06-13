<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, viewport-fit=cover">
    <title>Ma dette - Suivi & Paiement</title>
    <link href="https://fonts.googleapis.com/css2?family=Inter:ital,wght@0,300;0,400;0,500;0,600;0,700;1,400&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: 'Inter', sans-serif;
            background: linear-gradient(135deg, #0f2027 0%, #203a43 50%, #2c5364 100%);
            min-height: 100vh;
            padding: 24px;
        }
        .container { max-width: 1000px; margin: 0 auto; }
        .header {
            background: rgba(255,255,255,0.95);
            backdrop-filter: blur(10px);
            border-radius: 28px;
            padding: 32px;
            margin-bottom: 32px;
            text-align: center;
            position: relative;
        }
        .header h1 {
            background: linear-gradient(135deg, #667eea, #764ba2);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
            margin-bottom: 8px;
        }
        .debt-card {
            background: linear-gradient(135deg, #1e293b, #0f172a);
            border-radius: 28px;
            padding: 40px;
            margin-bottom: 32px;
            text-align: center;
            transition: transform 0.3s;
        }
        .debt-card:hover { transform: translateY(-5px); }
        .debt-label { color: #94a3b8; text-transform: uppercase; font-size: 0.85rem; margin-bottom: 16px; }
        .debt-amount { font-size: 4rem; font-weight: 800; color: #ef4444; margin: 20px 0; }
        .pay-btn-card {
            background: linear-gradient(135deg, #10b981, #059669);
            color: white;
            border: none;
            border-radius: 60px;
            padding: 14px 32px;
            font-weight: 700;
            font-size: 1.1rem;
            cursor: pointer;
            transition: all 0.3s;
            display: inline-flex;
            align-items: center;
            gap: 12px;
            box-shadow: 0 6px 16px rgba(16, 185, 129, 0.35);
            margin-top: 12px;
        }
        .pay-btn-card:hover {
            transform: translateY(-3px);
            box-shadow: 0 12px 24px rgba(16, 185, 129, 0.45);
        }
        .info-card {
            background: white;
            border-radius: 24px;
            padding: 28px;
            margin-bottom: 32px;
        }
        .info-row {
            display: flex;
            justify-content: space-between;
            padding: 14px 0;
            border-bottom: 1px solid #e2e8f0;
        }
        .info-row:last-child { border-bottom: none; }
        .info-label { font-weight: 600; color: #475569; }
        .info-value { color: #1e293b; font-weight: 500; }
        .section {
            background: white;
            border-radius: 24px;
            padding: 28px;
            margin-bottom: 32px;
        }
        .section h2 { margin-bottom: 20px; display: flex; align-items: center; gap: 10px; color: #1e293b; }
        .transaction-list { max-height: 600px; overflow-y: auto; }
        .transaction-item {
            padding: 16px;
            margin-bottom: 12px;
            border-radius: 16px;
            background: #f8fafc;
            border-left: 4px solid;
            transition: all 0.2s;
        }
        .transaction-item:hover { background: #f1f5f9; transform: translateX(5px); }
        .transaction-emprunt { border-left-color: #ef4444; }
        .transaction-remboursement { border-left-color: #10b981; }
        .transaction-interets { border-left-color: #f59e0b; }
        .refresh-btn {
            position: fixed;
            bottom: 24px;
            right: 24px;
            background: linear-gradient(135deg, #667eea, #764ba2);
            color: white;
            border: none;
            border-radius: 50px;
            padding: 14px 24px;
            cursor: pointer;
            display: flex;
            align-items: center;
            gap: 8px;
            font-weight: 600;
            transition: all 0.3s;
            box-shadow: 0 4px 12px rgba(0,0,0,0.15);
            z-index: 100;
        }
        .refresh-btn:hover { transform: translateY(-2px); box-shadow: 0 8px 20px rgba(0,0,0,0.2); }
        .last-update { text-align: center; color: #94a3b8; font-size: 0.75rem; margin-top: 20px; }
        .error-card {
            background: white;
            border-radius: 24px;
            padding: 48px;
            text-align: center;
        }
        .loading-spinner { text-align: center; padding: 60px; color: white; font-size: 1.2rem; }
        
        /* Modal styles */
        .modal-overlay {
            position: fixed;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: rgba(0,0,0,0.7);
            backdrop-filter: blur(8px);
            z-index: 2000;
            display: flex;
            align-items: center;
            justify-content: center;
            opacity: 0;
            visibility: hidden;
            transition: all 0.3s;
        }
        .modal-overlay.active {
            opacity: 1;
            visibility: visible;
        }
        .modal-content {
            background: white;
            border-radius: 32px;
            max-width: 500px;
            width: 90%;
            padding: 32px;
            transform: scale(0.9);
            transition: transform 0.3s;
            box-shadow: 0 25px 50px -12px rgba(0,0,0,0.5);
            max-height: 90vh;
            overflow-y: auto;
        }
        .modal-overlay.active .modal-content {
            transform: scale(1);
        }
        .modal-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 24px;
        }
        .modal-header h3 {
            font-size: 1.5rem;
            color: #1e293b;
        }
        .close-modal {
            background: none;
            border: none;
            font-size: 24px;
            cursor: pointer;
            color: #94a3b8;
            transition: color 0.2s;
            padding: 8px;
            border-radius: 50%;
            width: 40px;
            height: 40px;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        .close-modal:hover {
            color: #ef4444;
            background: #fef2f2;
        }
        .modal-amount-input {
            width: 100%;
            padding: 16px;
            font-size: 24px;
            text-align: center;
            border: 2px solid #e2e8f0;
            border-radius: 16px;
            margin: 16px 0;
            font-weight: 600;
        }
        .modal-amount-input:focus { outline: none; border-color: #667eea; }
        .modal-presets {
            display: flex;
            gap: 10px;
            margin: 16px 0;
            flex-wrap: wrap;
        }
        .preset-chip {
            background: #f1f5f9;
            padding: 8px 16px;
            border-radius: 40px;
            font-weight: 500;
            cursor: pointer;
            transition: all 0.2s;
        }
        .preset-chip:hover { background: #667eea; color: white; }
        .modal-fee-info {
            background: #f8fafc;
            padding: 16px;
            border-radius: 16px;
            margin: 16px 0;
            font-size: 14px;
        }
        .modal-fee-info .line {
            display: flex;
            justify-content: space-between;
            margin: 8px 0;
        }
        .modal-fee-info .total { font-weight: 700; color: #10b981; }
        .modal-fee-info .remaining { font-weight: 700; color: #ef4444; }
        .modal-submit {
            width: 100%;
            padding: 16px;
            background: linear-gradient(135deg, #10b981, #059669);
            color: white;
            border: none;
            border-radius: 40px;
            font-size: 18px;
            font-weight: 600;
            cursor: pointer;
            margin-top: 16px;
            transition: all 0.3s;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 12px;
            box-shadow: 0 4px 12px rgba(16, 185, 129, 0.3);
        }
        .modal-submit:disabled {
            opacity: 0.6;
            cursor: not-allowed;
        }
        .modal-submit:hover:not(:disabled) {
            transform: translateY(-2px);
            box-shadow: 0 8px 20px rgba(16, 185, 129, 0.4);
        }
        .modal-email-input {
            width: 100%;
            padding: 14px;
            font-size: 16px;
            border: 2px solid #e2e8f0;
            border-radius: 12px;
            margin: 8px 0 16px 0;
        }
        .modal-email-input:focus { outline: none; border-color: #667eea; }
        
        @media (max-width: 768px) {
            body { padding: 16px; }
            .debt-amount { font-size: 2.5rem; }
            .info-row { flex-direction: column; gap: 6px; }
        }
        @keyframes slideIn {
            from { transform: translateX(100%); opacity: 0; }
            to { transform: translateX(0); opacity: 1; }
        }
        .notification {
            position: fixed;
            top: 20px;
            right: 20px;
            background: #10b981;
            color: white;
            padding: 12px 20px;
            border-radius: 12px;
            z-index: 2000;
            animation: slideIn 0.3s ease;
            font-weight: 500;
            box-shadow: 0 4px 12px rgba(0,0,0,0.15);
        }
        .required {
            color: #ef4444;
            margin-left: 4px;
        }
    </style>
</head>
<body>
    <div class="container" id="app">
        <div class="loading-spinner"><i class="fas fa-spinner fa-spin"></i> Chargement de vos données...</div>
    </div>
    <button class="refresh-btn" onclick="location.reload()"><i class="fas fa-sync-alt"></i> Actualiser</button>

    <!-- Modal de paiement -->
    <div id="paymentModal" class="modal-overlay">
        <div class="modal-content">
            <div class="modal-header">
                <h3><i class="fas fa-hand-holding-usd"></i> Remboursement</h3>
                <button class="close-modal" id="closeModalBtn"><i class="fas fa-times"></i></button>
            </div>
            <div>
                <label style="font-weight:600;">Email <span class="required">*</span></label>
                <input type="email" id="paymentEmail" class="modal-email-input" placeholder="votre@email.com" required>
                
                <label style="font-weight:600;">Montant à me verser (TTC)</label>
                <input type="number" id="paymentAmount" class="modal-amount-input" step="0.01" min="0" value="0">
                <div class="modal-presets">
                    <span class="preset-chip" data-amount="10">+10€</span>
                    <span class="preset-chip" data-amount="20">+20€</span>
                    <span class="preset-chip" data-amount="50">+50€</span>
                    <span class="preset-chip" data-amount="100">+100€</span>
                    <span class="preset-chip" id="maxPreset">💳 Max</span>
                </div>
            </div>
            <div id="modalFeeInfo" class="modal-fee-info">
                <div class="line"><span>💰 Vous payez :</span><span id="grossAmount">0.00 €</span></div>
                <div class="line"><span>📊 Frais Dodo (10%) :</span><span id="feeAmount">0.00 €</span></div>
                <div class="line total remaining"><span>💪 Dette restante après paiement :</span><span id="remainingDebt">0.00 €</span></div>
            </div>
            <button id="confirmPaymentBtn" class="modal-submit">
                <i class="fas fa-lock"></i> Payer en ligne
                <i class="fas fa-arrow-right"></i>
            </button>
        </div>
    </div>

    <script type="module">
        import { initializeApp } from "https://www.gstatic.com/firebasejs/12.14.0/firebase-app.js";
        import { getFirestore, doc, getDoc, onSnapshot, updateDoc, arrayUnion, Timestamp } from "https://www.gstatic.com/firebasejs/12.14.0/firebase-firestore.js";
        import { getAnalytics } from "https://www.gstatic.com/firebasejs/12.14.0/firebase-analytics.js";

        // ============================================
        // CONFIGURATION FIREBASE
        // ============================================
        const firebaseConfig = {
            apiKey: "AIzaSyDt1q740HCXf0gRp0fADRtfCsdcWqUpBCE",
            authDomain: "gestion-dettes-fcea1.firebaseapp.com",
            projectId: "gestion-dettes-fcea1",
            storageBucket: "gestion-dettes-fcea1.firebasestorage.app",
            messagingSenderId: "673790821106",
            appId: "1:673790821106:web:80e6bf9b24f53f2f37866b",
            measurementId: "G-1LQ8QRHNF0"
        };

        // ============================================
        // CONFIGURATION DODO PAYMENTS
        // ============================================
        const DODO_PUBLIC_KEY = "pk_snd_091bba0fefcd4852a44cccdcf47602b5";
        const DODO_API_URL = "https://api.dodopayments.com/v1";
        const PRODUCT_ID = "pdt_0Ngya0h3KKlfI1ujAbuUP";
        const TRANSACTION_FEE_RATE = 0.10;
        const WEBHOOK_URL = "https://lost-cyrano.github.io/dettes/webhooks/DodoPayements/";
        
        // ============================================
        // INITIALISATION FIREBASE
        // ============================================
        const app = initializeApp(firebaseConfig);
        const analytics = getAnalytics(app);
        const db = getFirestore(app);
        
        let currentPerson = null;
        let currentPersonId = null;
        let unsubscribeListener = null;
        
        // ============================================
        // FONCTIONS UTILITAIRES
        // ============================================
        function getPersonIdFromUrl() {
            const params = new URLSearchParams(window.location.search);
            return params.get('id');
        }
        
        function calculateMaxAllowedAmount(debt) {
            if (debt <= 0) return 0;
            const rawMax = debt / (1 - TRANSACTION_FEE_RATE);
            return Math.ceil(rawMax * 100) / 100;
        }
        
        function showNotification(message, type = 'success') {
            const notification = document.createElement('div');
            notification.className = 'notification';
            notification.style.background = type === 'error' ? '#ef4444' : '#10b981';
            notification.innerHTML = `<i class="fas ${type === 'error' ? 'fa-exclamation-triangle' : 'fa-check-circle'}"></i> ${message}`;
            document.body.appendChild(notification);
            setTimeout(() => notification.remove(), 4000);
        }
        
        function showError(msg) {
            document.getElementById('app').innerHTML = `
                <div class="error-card">
                    <i class="fas fa-exclamation-triangle" style="font-size:3rem; color:#ef4444; margin-bottom:20px;"></i>
                    <h2 style="color:#ef4444; margin-bottom:16px;">Erreur</h2>
                    <p>${msg}</p>
                    <button onclick="location.reload()" style="margin-top:24px; padding:12px 24px; background:linear-gradient(135deg, #667eea, #764ba2); color:white; border:none; border-radius:12px; cursor:pointer;">
                        <i class="fas fa-sync-alt"></i> Réessayer
                    </button>
                </div>
            `;
        }
        
        function getFrequencyLabel(freq) {
            const labels = { daily: 'Quotidienne', weekly: 'Hebdomadaire', monthly: 'Mensuelle' };
            return labels[freq] || freq;
        }
        
        function getTransactionIcon(type) {
            const icons = { emprunt: '💰', remboursement: '💳', interets: '📈' };
            return icons[type] || '📝';
        }
        
        function getTransactionLabel(type) {
            const labels = { emprunt: 'Emprunt', remboursement: 'Remboursement', interets: 'Intérêts' };
            return labels[type] || type;
        }
        
        function escapeHtml(str) {
            if (!str) return '';
            return str.replace(/[&<>]/g, function(m) {
                if (m === '&') return '&amp;';
                if (m === '<') return '&lt;';
                if (m === '>') return '&gt;';
                return m;
            });
        }
        
        // ============================================
        // MISE À JOUR DE LA DETTE DANS FIREBASE
        // ============================================
        async function updateDebtAfterPayment(grossAmountPaid, transactionId, userEmail) {
            if (!currentPersonId || !currentPerson) return false;
            
            const fee = grossAmountPaid * TRANSACTION_FEE_RATE;
            const debtReduction = grossAmountPaid - fee;
            
            if (debtReduction <= 0) {
                showNotification(`Paiement de ${grossAmountPaid.toFixed(2)}€ reçu, mais frais de ${fee.toFixed(2)}€ = aucune réduction de dette`, 'error');
                return false;
            }
            
            const oldDebt = currentPerson.currentDebt || 0;
            const newDebt = Math.max(0, oldDebt - debtReduction);
            const today = new Date().toISOString().split('T')[0];
            
            const transaction = {
                type: "remboursement",
                amount: debtReduction,
                grossAmount: grossAmountPaid,
                fee: fee,
                date: today,
                description: `Paiement en ligne (ID: ${transactionId}) - Frais 10% déduits - Email: ${userEmail}`,
                timestamp: Timestamp.now()
            };
            
            try {
                const debtorRef = doc(db, "debtors", currentPersonId);
                await updateDoc(debtorRef, {
                    currentDebt: newDebt,
                    transactions: arrayUnion(transaction)
                });
                showNotification(`✅ Remboursement appliqué ! Dette réduite de ${debtReduction.toFixed(2)}€`, 'success');
                return true;
            } catch (error) {
                console.error("Erreur mise à jour Firebase:", error);
                showNotification("Erreur lors de la mise à jour de la dette", 'error');
                return false;
            }
        }
        
        // ============================================
        // CRÉATION D'UNE SESSION DODO
        // ============================================
        async function createDodoCheckoutSession(grossAmount, userEmail) {
            if (grossAmount < 0) {
                showNotification("Montant invalide", 'error');
                return null;
            }
            
            if (!userEmail || !userEmail.includes('@')) {
                showNotification("Veuillez entrer un email valide", 'error');
                return null;
            }
            
            const amountInCents = Math.round(grossAmount * 100);
            const successUrl = `${window.location.origin}${window.location.pathname}?payment_success=true`;
            const cancelUrl = `${window.location.origin}${window.location.pathname}?payment_cancel=true`;
            
            const payload = {
                product_cart: [
                    {
                        product_id: PRODUCT_ID,
                        quantity: 1,
                        amount: amountInCents
                    }
                ],
                success_url: successUrl,
                cancel_url: cancelUrl,
                customer_email: userEmail,
                metadata: {
                    debtor_id: currentPersonId,
                    debtor_name: currentPerson?.name || "Inconnu",
                    gross_amount: grossAmount,
                    transaction_fee_rate: TRANSACTION_FEE_RATE,
                    webhook_url: WEBHOOK_URL
                }
            };
            
            try {
                const response = await fetch(`${DODO_API_URL}/checkout/session`, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                        'Authorization': `Bearer ${DODO_PUBLIC_KEY}`
                    },
                    body: JSON.stringify(payload)
                });
                
                if (!response.ok) {
                    const errorText = await response.text();
                    throw new Error(`Erreur Dodo: ${response.status} ${errorText}`);
                }
                
                const session = await response.json();
                return session;
            } catch (error) {
                console.error("Erreur création session Dodo:", error);
                showNotification(`Impossible de créer le paiement: ${error.message}`, 'error');
                return null;
            }
        }
        
        // ============================================
        // GESTION MODALE DE PAIEMENT
        // ============================================
        let currentMaxAllowed = 0;
        
        function updateModalPreview() {
            const amountInput = document.getElementById('paymentAmount');
            let gross = parseFloat(amountInput.value);
            if (isNaN(gross)) gross = 0;
            if (gross < 0) gross = 0;
            
            if (gross > currentMaxAllowed && currentMaxAllowed > 0) {
                gross = currentMaxAllowed;
                amountInput.value = gross.toFixed(2);
            }
            
            const fee = gross * TRANSACTION_FEE_RATE;
            const net = gross - fee;
            const currentDebt = currentPerson?.currentDebt || 0;
            const remainingDebt = Math.max(0, currentDebt - net);
            
            document.getElementById('grossAmount').textContent = gross.toFixed(2) + ' €';
            document.getElementById('feeAmount').textContent = fee.toFixed(2) + ' €';
            document.getElementById('remainingDebt').textContent = remainingDebt.toFixed(2) + ' €';
        }
        
        function openPaymentModal() {
            if (!currentPerson) {
                showNotification("Données non chargées", 'error');
                return;
            }
            
            const currentDebt = currentPerson.currentDebt || 0;
            currentMaxAllowed = calculateMaxAllowedAmount(currentDebt);
            
            if (currentDebt <= 0) {
                showNotification("Vous n'avez plus aucune dette à rembourser ! 🎉", 'success');
                return;
            }
            
            const modal = document.getElementById('paymentModal');
            const amountInput = document.getElementById('paymentAmount');
            const emailInput = document.getElementById('paymentEmail');
            
            amountInput.value = "0";
            emailInput.value = "";
            updateModalPreview();
            modal.classList.add('active');
        }
        
        function closePaymentModal() {
            document.getElementById('paymentModal').classList.remove('active');
        }
        
        async function confirmPayment() {
            const amountInput = document.getElementById('paymentAmount');
            const emailInput = document.getElementById('paymentEmail');
            
            let grossAmount = parseFloat(amountInput.value);
            if (isNaN(grossAmount)) grossAmount = 0;
            if (grossAmount < 0) grossAmount = 0;
            
            const userEmail = emailInput.value.trim();
            if (!userEmail || !userEmail.includes('@')) {
                showNotification("Veuillez entrer une adresse email valide", 'error');
                return;
            }
            
            if (grossAmount > currentMaxAllowed && currentMaxAllowed > 0) {
                grossAmount = currentMaxAllowed;
            }
            
            if (grossAmount <= 0) {
                showNotification("Le montant doit être supérieur à 0€", 'error');
                return;
            }
            
            const confirmBtn = document.getElementById('confirmPaymentBtn');
            confirmBtn.disabled = true;
            confirmBtn.innerHTML = '<i class="fas fa-spinner fa-spin"></i> Création du paiement...';
            
            try {
                const session = await createDodoCheckoutSession(grossAmount, userEmail);
                if (session && session.checkout_url) {
                    sessionStorage.setItem('pendingPayment', JSON.stringify({
                        grossAmount: grossAmount,
                        debtorId: currentPersonId,
                        userEmail: userEmail,
                        timestamp: Date.now()
                    }));
                    window.location.href = session.checkout_url;
                } else {
                    showNotification("Erreur: impossible de créer la session de paiement", 'error');
                }
            } catch (error) {
                console.error(error);
                showNotification("Erreur technique, veuillez réessayer", 'error');
            } finally {
                confirmBtn.disabled = false;
                confirmBtn.innerHTML = '<i class="fas fa-lock"></i> Payer en ligne <i class="fas fa-arrow-right"></i>';
            }
        }
        
        // ============================================
        // GESTION DU RETOUR APRÈS PAIEMENT
        // ============================================
        async function handlePaymentReturn() {
            const urlParams = new URLSearchParams(window.location.search);
            const paymentSuccess = urlParams.get('payment_success');
            const paymentCancel = urlParams.get('payment_cancel');
            
            if (paymentSuccess === 'true') {
                const pending = sessionStorage.getItem('pendingPayment');
                if (pending) {
                    const { grossAmount, debtorId, userEmail } = JSON.parse(pending);
                    sessionStorage.removeItem('pendingPayment');
                    
                    if (debtorId === currentPersonId) {
                        showNotification("Paiement réussi ! Mise à jour de votre dette...", 'success');
                        await updateDebtAfterPayment(grossAmount, 'dodo_' + Date.now(), userEmail);
                        await loadPersonData();
                    }
                } else {
                    showNotification("Paiement réussi ! Rafraîchissement des données...", 'success');
                    await loadPersonData();
                }
                window.history.replaceState({}, document.title, window.location.pathname);
            } else if (paymentCancel === 'true') {
                showNotification("Paiement annulé", 'error');
                window.history.replaceState({}, document.title, window.location.pathname);
            }
        }
        
        // ============================================
        // CHARGEMENT DES DONNÉES FIREBASE
        // ============================================
        async function loadPersonData() {
            const docRef = doc(db, "debtors", currentPersonId);
            const docSnap = await getDoc(docRef);
            
            if (docSnap.exists()) {
                currentPerson = { id: docSnap.id, ...docSnap.data() };
                renderPage();
                setupRealtimeListener();
                await handlePaymentReturn();
            } else {
                showError("Personne non trouvée - Lien invalide ou expiré");
            }
        }
        
        function setupRealtimeListener() {
            if (unsubscribeListener) unsubscribeListener();
            
            const docRef = doc(db, "debtors", currentPersonId);
            unsubscribeListener = onSnapshot(docRef, (docSnap) => {
                if (docSnap.exists()) {
                    const newData = { id: docSnap.id, ...docSnap.data() };
                    if (JSON.stringify(newData) !== JSON.stringify(currentPerson)) {
                        currentPerson = newData;
                        renderPage();
                        showNotification("Mise à jour des données en temps réel");
                    }
                }
            }, (error) => {
                console.error("Realtime error:", error);
            });
        }
        
        function renderPage() {
            const app = document.getElementById('app');
            const transactions = [...(currentPerson.transactions || [])].sort((a,b) => new Date(b.date) - new Date(a.date));
            const monthlyInterest = (currentPerson.currentDebt || 0) * ((currentPerson.interestRate || 0) / 100) / 12;
            const dailyInterest = (currentPerson.currentDebt || 0) * ((currentPerson.interestRate || 0) / 100) / 365;
            
            app.innerHTML = `
                <div class="header">
                    <h1><i class="fas fa-coins"></i> Suivi de ma dette</h1>
                    <p>Bonjour <strong>${escapeHtml(currentPerson.name)}</strong></p>
                </div>
                <div class="debt-card">
                    <div class="debt-label">Montant actuel dû</div>
                    <div class="debt-amount">${(currentPerson.currentDebt || 0).toFixed(2)} €</div>
                    <button class="pay-btn-card" id="cardPayBtn">
                        <i class="fas fa-credit-card"></i> Rembourser en ligne
                        <i class="fas fa-arrow-right"></i>
                    </button>
                </div>
                <div class="info-card">
                    <div class="info-row"><span class="info-label"><i class="fas fa-percent"></i> Taux d'intérêt</span><span class="info-value">${currentPerson.interestRate || 0}%</span></div>
                    <div class="info-row"><span class="info-label"><i class="fas fa-calendar-alt"></i> Fréquence</span><span class="info-value">${getFrequencyLabel(currentPerson.frequency || 'monthly')}</span></div>
                    <div class="info-row"><span class="info-label"><i class="fas fa-chart-line"></i> Intérêts mensuels estimés</span><span class="info-value">${monthlyInterest.toFixed(2)} €</span></div>
                    <div class="info-row"><span class="info-label"><i class="fas fa-chart-line"></i> Intérêts journaliers</span><span class="info-value">${dailyInterest.toFixed(4)} €</span></div>
                    <div class="info-row"><span class="info-label"><i class="fas fa-clock"></i> Dernière mise à jour</span><span class="info-value">${currentPerson.lastInterestUpdate || 'N/A'}</span></div>
                </div>
                <div class="section">
                    <h2><i class="fas fa-history"></i> Historique des transactions</h2>
                    <div class="transaction-list" id="transactionList"></div>
                </div>
                <div class="last-update">
                    <i class="fas fa-clock"></i> Dernière actualisation: ${new Date().toLocaleString()}
                </div>
            `;
            
            const container = document.getElementById('transactionList');
            if (transactions.length === 0) {
                container.innerHTML = '<p style="text-align:center; color:#94a3b8; padding:40px;"><i class="fas fa-inbox"></i> Aucune transaction</p>';
            } else {
                const recent = transactions.slice(0, 50);
                recent.forEach(t => {
                    const div = document.createElement('div');
                    div.className = `transaction-item transaction-${t.type}`;
                    let amountDisplay = t.amount;
                    if (t.type === 'remboursement' && t.grossAmount) {
                        amountDisplay = `${t.amount.toFixed(2)} € (payé ${t.grossAmount.toFixed(2)}€ - frais ${t.fee.toFixed(2)}€)`;
                    } else {
                        amountDisplay = `${t.amount.toFixed(2)} €`;
                    }
                    div.innerHTML = `
                        <div style="font-size:0.8rem; color:#64748b; margin-bottom:5px;">📅 ${t.date}</div>
                        <div style="font-weight:600; margin-bottom:5px;">${getTransactionIcon(t.type)} ${getTransactionLabel(t.type)}</div>
                        <div style="font-size:1.1rem; font-weight:700;">${amountDisplay}</div>
                        ${t.description ? `<div style="margin-top:5px; font-size:0.85rem; color:#64748b;"><i class="fas fa-comment"></i> ${escapeHtml(t.description)}</div>` : ''}
                    `;
                    container.appendChild(div);
                });
                if (transactions.length > 50) {
                    const info = document.createElement('p');
                    info.style.textAlign = 'center';
                    info.style.color = '#94a3b8';
                    info.style.marginTop = '10px';
                    info.innerHTML = `<i class="fas fa-info-circle"></i> Affichage des 50 dernières transactions sur ${transactions.length}`;
                    container.appendChild(info);
                }
            }
            
            const cardPayBtn = document.getElementById('cardPayBtn');
            if (cardPayBtn) cardPayBtn.addEventListener('click', openPaymentModal);
        }
        
        async function loadData() {
            const id = getPersonIdFromUrl();
            if (!id) { showError("Lien invalide - Identifiant manquant"); return; }
            currentPersonId = id;
            await loadPersonData();
        }
        
        // ============================================
        // INITIALISATION DES ÉCOUTEURS MODALE
        // ============================================
        function initModalListeners() {
            const amountInput = document.getElementById('paymentAmount');
            if (amountInput) {
                amountInput.addEventListener('input', updateModalPreview);
            }
            
            const emailInput = document.getElementById('paymentEmail');
            if (emailInput) {
                emailInput.addEventListener('input', updateModalPreview);
            }
            
            document.querySelectorAll('.preset-chip[data-amount]').forEach(btn => {
                btn.addEventListener('click', (e) => {
                    const amount = parseFloat(btn.dataset.amount);
                    if (!isNaN(amount)) {
                        const input = document.getElementById('paymentAmount');
                        if (input) {
                            let val = amount;
                            if (val > currentMaxAllowed && currentMaxAllowed > 0) val = currentMaxAllowed;
                            input.value = val.toFixed(2);
                            updateModalPreview();
                        }
                    }
                });
            });
            
            const maxPreset = document.getElementById('maxPreset');
            if (maxPreset) {
                maxPreset.addEventListener('click', () => {
                    if (currentMaxAllowed > 0) {
                        document.getElementById('paymentAmount').value = currentMaxAllowed.toFixed(2);
                        updateModalPreview();
                    }
                });
            }
            
            const confirmBtn = document.getElementById('confirmPaymentBtn');
            if (confirmBtn) {
                confirmBtn.addEventListener('click', confirmPayment);
            }
            
            const closeBtn = document.getElementById('closeModalBtn');
            if (closeBtn) {
                closeBtn.addEventListener('click', closePaymentModal);
            }
            
            const modal = document.getElementById('paymentModal');
            if (modal) {
                modal.addEventListener('click', (e) => {
                    if (e.target === modal) closePaymentModal();
                });
            }
        }
        
        window.addEventListener('beforeunload', () => {
            if (unsubscribeListener) unsubscribeListener();
        });
        
        initModalListeners();
        loadData();
    </script>
</body>
</html>
